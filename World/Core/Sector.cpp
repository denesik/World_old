// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Sector.h"

#include <glm/glm.hpp>
#include <stdint.h>
#include "RenderAgent.h"
#include "../Graphic/GameRender/ModelBlockGenerator.h"
#include "../Graphic/Render/MultiModel.h"
#include "../Graphic/RegistryGraphic.h"
#include "RegistryCore.h"
#include "MapGen/PerlinNoise.h"
#include "../Log.h"

static PerlinNoise noise(0);

Sector::Sector(const glm::ivec3 &position)
  : mPos(position)
{
  glm::ivec3 pos;
//   for (pos.z = -SECTOR_RADIUS; pos.z <= SECTOR_RADIUS; ++pos.z)
//   {
//     for (pos.y = -SECTOR_RADIUS; pos.y <= SECTOR_RADIUS; ++pos.y)
//     {
//       for (pos.x = -SECTOR_RADIUS; pos.x <= SECTOR_RADIUS; ++pos.x)
//       {
//         auto &block = mBlocks[pos.z + SECTOR_RADIUS][pos.y + SECTOR_RADIUS][pos.x + SECTOR_RADIUS];
// 
//         if (pos.z == -2)
//         {
//           block = REGISTRY_CORE.GetBlocksLibrary().Create(StringIntern(pos.x % 2 ? "BlockSand" : "BlockStone"));
//         }
//         else
//         {
//           block = nullptr;
//         }
//       }
//     }
//   }
  auto currentTime = glfwGetTime();

  for (pos.y = -SECTOR_RADIUS; pos.y <= SECTOR_RADIUS; ++pos.y)
  {
    for (pos.x = -SECTOR_RADIUS; pos.x <= SECTOR_RADIUS; ++pos.x)
    {
      float tx = mPos.x * SECTOR_SIZE + static_cast<int32_t>(pos.x);
      float ty = mPos.y * SECTOR_SIZE + static_cast<int32_t>(pos.y);
      float h = noise.Noise2(tx / 10.0f, ty / 10.0f);
      int32_t zh = glm::round(h * SECTOR_RADIUS);
      for (pos.z = -SECTOR_RADIUS; pos.z <= SECTOR_RADIUS; ++pos.z)
      {
        auto &block = mBlocks[pos.z + SECTOR_RADIUS][pos.y + SECTOR_RADIUS][pos.x + SECTOR_RADIUS];
        if (pos.z <= zh)
        {
          block = REGISTRY_CORE.GetBlocksLibrary().Create(StringIntern(pos.x % 2 ? "BlockSand" : "BlockStone"));
        }
        else
        {
          block = nullptr;
        }
      }
    }
  }

  LOG(info) << "SectorGen: " << glfwGetTime() - currentTime;
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
  assert(glm::clamp(pos, static_cast<int32_t>(-SECTOR_RADIUS), static_cast<int32_t>(SECTOR_RADIUS)) == pos);

  return mBlocks[pos.z + SECTOR_RADIUS][pos.y + SECTOR_RADIUS][pos.x + SECTOR_RADIUS];
}

void Sector::Update(class World *world)
{
  auto currentTime = glfwGetTime();
  glm::ivec3 pos;
  for (pos.z = -SECTOR_RADIUS; pos.z <= SECTOR_RADIUS; ++pos.z)
  {
    for (pos.y = -SECTOR_RADIUS; pos.y <= SECTOR_RADIUS; ++pos.y)
    {
      for (pos.x = -SECTOR_RADIUS; pos.x <= SECTOR_RADIUS; ++pos.x)
      {
        auto &block = mBlocks[pos.z + SECTOR_RADIUS][pos.y + SECTOR_RADIUS][pos.x + SECTOR_RADIUS];

        if (block)
        {
          static StringIntern renderAgentName("RenderAgent");
          static_cast<RenderAgent *>(block->GetFromFullName(renderAgentName))->Update(
            { world , this, mPos * static_cast<int32_t>(Sector::SECTOR_SIZE) + pos }
          );
        }
      }
    }
  }

  if (mRenderSector.IsNeedBuild())
  {
    LOG(info) << "SectorBuild: " << glfwGetTime() - currentTime;
  }

  mRenderSector.Update();
}

RenderSector &Sector::GetRenderSector()
{
  return mRenderSector;
}
