// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Sector.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdint.h>
#include "RenderAgent.h"
#include "RegistryCore.h"
#include "MapGen/PerlinNoise.h"
#include "../Log.h"

static PerlinNoise noise(0);

Sector::Sector(const glm::ivec3 &position)
  : mPos(position)
{
  auto currentTime = glfwGetTime();

  {
    glm::ivec3 pos;
    size_t index = 0;
    for (pos.z = -SECTOR_RADIUS; pos.z <= SECTOR_RADIUS; ++pos.z)
    {
      for (pos.y = -SECTOR_RADIUS; pos.y <= SECTOR_RADIUS; ++pos.y)
      {
        for (pos.x = -SECTOR_RADIUS; pos.x <= SECTOR_RADIUS; ++pos.x)
        {
          mBlocksPos[index++] = mPos * static_cast<int32_t>(SECTOR_SIZE) + pos;
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
    float h = noise.Noise2(tx / 10.0f, ty / 10.0f);
    int32_t zh = static_cast<int32_t>(glm::round(h * SECTOR_RADIUS));
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

const glm::ivec3 & Sector::GetSectorPosition() const
{
  return mPos;
}

PGameObject Sector::GetBlock(const glm::ivec3 &pos)
{
  //assert(glm::clamp(pos, static_cast<int32_t>(-SECTOR_RADIUS), static_cast<int32_t>(SECTOR_RADIUS)) == pos);

  return mBlocks[(pos.z + SECTOR_RADIUS) * SECTOR_SIZE * SECTOR_SIZE + (pos.y + SECTOR_RADIUS) * SECTOR_SIZE + pos.x + SECTOR_RADIUS];
}

void Sector::Update(class World *world)
{
  auto currentTime = glfwGetTime();

  GameObjectParams params{ world , this, {} };
  for (size_t i = 0; i < mBlocks.size(); ++i)
  {
    if (mBlocks[i])
    {
      params.pos = mBlocksPos[i];
      mBlocks[i]->Update(params);
    }
  }

  if (mRenderSector.IsNeedBuild())
  {
    LOG(info) << "SectorBuild: " << glfwGetTime() - currentTime;
  }
  mRenderSector.Update();
}

void Sector::Draw(class World *world)
{
  mRenderSector.Draw();
}

RenderSector &Sector::GetRenderSector()
{
  return mRenderSector;
}
