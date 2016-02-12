// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Sector.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdint.h>
#include "../tools/Log.h"

Sector::Sector(const SPos &position)
  : mPos(position)
{
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
  assert(glm::clamp(pos, 0, static_cast<int32_t>(SECTOR_SIZE - 1)) == pos);
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
        mBlocks[i]->Draw(params);
      }
    }
    LOG(trace) << "SectorBuild: " << glfwGetTime() - currentTime;
  }
  mRenderSector.Update();
}

RenderSector &Sector::GetRenderSector()
{
  return mRenderSector;
}
