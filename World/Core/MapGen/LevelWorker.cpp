// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include <GLFW\glfw3.h>
#include "LevelWorker.h"
#include <thread>
#include "tools\CoordSystem.h"
#include "Log.h"
#include "Core\Sector.h"
#include "Core\MapGen\PerlinNoise.h"
#include "Core\RenderSector.h"
#include "..\DB.h"

LevelWorker::LevelWorker()
{
}

std::shared_ptr<Sector> LevelWorker::GetSector(const SPos &v)
{
  std::lock_guard<std::mutex> scope(async_process);
  mLast = v;

	auto f = ready.find(v);
	if (f != ready.end())
		return f->second;

	if (requested.find(v) == requested.end())
	  requested.insert(v);

	return nullptr;
}

static PerlinNoise noise(0);

//TODO: ñòîèò âûíåñòè â êëàññ ãåíåðàòîð êàðòû, ñèíõðîííûé âûçîâ
std::shared_ptr<Sector> LevelWorker::Generate(const SPos &spos)
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

void LevelWorker::Process()
{
  async_process.lock();
	if (!requested.empty())
	{
    SPos last = mLast;
    auto r = requested.find(last);
    if(r == requested.end())
      r = requested.begin();
    async_process.unlock();

    auto gen = Generate(*r);

    async_process.lock();
    ready[*r] = gen;
    requested.erase(r);
    async_process.unlock();
	}
  else
    async_process.unlock();
}
