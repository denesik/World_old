// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Sector.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdint.h>
#include "RegistryCore.h"
#include "MapGen/PerlinNoise.h"
#include "../Log.h"

static PerlinNoise noise(0);

Sector::Sector(const SPos &position, RenderSector &renderSector)
  : mPos(position), mRenderSector(renderSector)
{
  auto currentTime = glfwGetTime();

  {
    SBPos pos;
    size_t index = 0;
    for (pos.z = 0; pos.z < SECTOR_SIZE; ++pos.z)
    {
      for (pos.y = 0; pos.y < SECTOR_SIZE; ++pos.y)
      {
        for (pos.x = 0; pos.x < SECTOR_SIZE; ++pos.x)
        {
          mBlocksPos[index++] = pos;
        }
      }
    }
  }

  size_t blocksCount = 0;

  for (size_t i = 0; i < mBlocks.size(); ++i)
  {
    const auto &pos = mBlocksPos[i];
    float tx = static_cast<float>(pos.x);
    float ty = static_cast<float>(pos.y);
    float h = (noise.Noise2(tx / 10.0f, ty / 10.0f) + 1.0f) / 2.0f;
    int32_t zh = static_cast<int32_t>(glm::round(h * (SECTOR_SIZE - 1)));
    if (pos.z <= zh)
    {
      mBlocks[i] = REGISTRY_CORE.GetBlocksLibrary().Create(StringIntern(pos.x % 2 ? "BlockSand" : "BlockStone"));
      ++blocksCount;
    }
    else
    {
      mBlocks[i] = nullptr;
    }
  }

  LOG(info) << "SectorGen: " << glfwGetTime() - currentTime << " blocks count: " << blocksCount;
}


Sector::~Sector()
{
}

const SPos & Sector::GetSectorPosition() const
{
  return mPos;
}

PBlock Sector::GetBlock(const SBPos &pos)
{
  //assert(glm::clamp(pos, static_cast<int32_t>(-SECTOR_RADIUS), static_cast<int32_t>(SECTOR_RADIUS)) == pos);

  return mBlocks[pos.z * SECTOR_SIZE * SECTOR_SIZE + pos.y * SECTOR_SIZE + pos.x];
}

void Sector::SetBlock(const SBPos &pos, PBlock block)
{
  mBlocks[pos.z * SECTOR_SIZE * SECTOR_SIZE + pos.y * SECTOR_SIZE + pos.x] = block;
}

void Sector::Update(class World *world)
{
  auto currentTime = glfwGetTime();

  GameObjectParams params{ world , this, {} };
//   for (size_t i = 0; i < mBlocks.size(); ++i)
//   {
//     if (mBlocks[i] && !mBlocks[i]->IsStatic())
//     {
//       params.pos = mPos + static_cast<glm::ivec3>(mBlocksPos[i]);
//       mBlocks[i]->Update(params);
//     }
//   }

  if (mRenderSector.IsNeedBuild())
  {
    for (size_t i = 0; i < mBlocks.size(); ++i)
    {
      if (mBlocks[i])
      {
        params.pos = mPos * static_cast<int32_t>(SECTOR_SIZE) + mBlocksPos[i];
        mBlocks[i]->UpdateGraphic(params);
      }
    }
    LOG(info) << "SectorBuild: " << glfwGetTime() - currentTime;
  }
  mRenderSector.Update();
}

RenderSector &Sector::GetRenderSector()
{
  return mRenderSector;
}
