// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include <GLFW\glfw3.h>
#include "WorldWorker.h"
#include <thread>
#include "tools\CoordSystem.h"
#include "Log.h"
#include "Core\Sector.h"
#include "Core\MapGen\PerlinNoise.h"
#include "Core\RenderSector.h"
#include "..\DB.h"

WorldWorker::WorldWorker()
{
}

std::shared_ptr<Sector> WorldWorker::GetSector(const SPos &v)
{
  std::lock_guard<std::mutex> scope(mQueueMutex);
  mLast = v;

	auto f = mReady.find(v);
	if (f != mReady.end())
		return f->second;

	if (mRequested.find(v) == mRequested.end())
	  mRequested.insert(v);

	return nullptr;
}

static PerlinNoise noise(0);

std::shared_ptr<Sector> WorldWorker::Generate(const SPos &spos)
{
	auto currentTime = glfwGetTime(); //TODO: totally unnecessary
	std::shared_ptr<Sector> psec = std::make_shared<Sector>(spos);
	Sector &s = *psec;

	{
		SBPos pos;
		size_t index = 0;
		for (pos.z = 0; pos.z < SECTOR_SIZE; ++pos.z)
		{
			for (pos.y = 0; pos.y < SECTOR_SIZE; ++pos.y)
			{
				for (pos.x = 0; pos.x < SECTOR_SIZE; ++pos.x)
				{
					s.mBlocksPos[index++] = pos;
				}
			}
		}
	}

	size_t blocksCount = 0;

	for (size_t i = 0; i < s.mBlocks.size(); ++i)
	{
		const auto &pos = s.mBlocksPos[i];
		float tx = static_cast<float>(pos.x);
		float ty = static_cast<float>(pos.y);
		float h = (noise.Noise2(tx / 10.0f, ty / 10.0f) + 1.0f) / 2.0f;
		int32_t zh = static_cast<int32_t>(glm::round(h * (SECTOR_SIZE - 1)));
		if (pos.z <= zh)
		{
			s.mBlocks[i] = DB::Get().Create(StringIntern(pos.x % 2 ? "BlockSand" : "BlockStone"));
			++blocksCount;
		}
		else
		{
			s.mBlocks[i] = nullptr;
		}
	}
  psec->mRenderSector.Changed();

	LOG(trace) << "SectorGen: " << glfwGetTime() - currentTime << " blocks count: " << blocksCount;
  return psec;
}

void WorldWorker::Process()
{
  mQueueMutex.lock();
	if (!mRequested.empty())
	{
    SPos last = mLast;
    auto r = mRequested.find(last);
    if(r == mRequested.end())
      r = mRequested.begin();
    mQueueMutex.unlock();

    auto gen = Generate(*r);

    mQueueMutex.lock();
    mReady[*r] = gen;
    mRequested.erase(r);
    mQueueMutex.unlock();
	}
  else
    mQueueMutex.unlock();
}
