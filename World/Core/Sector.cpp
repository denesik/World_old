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


Sector::Sector(const glm::ivec3 &position)
  : mSectorPosition(position)
{
  glm::ivec3 pos;
  for (pos.z = -SECTOR_RADIUS; pos.z <= SECTOR_RADIUS; ++pos.z)
  {
    for (pos.y = -SECTOR_RADIUS; pos.y <= SECTOR_RADIUS; ++pos.y)
    {
      for (pos.x = -SECTOR_RADIUS; pos.x <= SECTOR_RADIUS; ++pos.x)
      {
        auto &block = mBlocks[pos.z + SECTOR_RADIUS][pos.y + SECTOR_RADIUS][pos.x + SECTOR_RADIUS];

        if (pos.z == -2)
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
}


Sector::~Sector()
{
}

const glm::ivec3 & Sector::GetSectorPosition() const
{
  return mSectorPosition;
}

PGameObject Sector::GetBlock(const glm::ivec3 &pos)
{
  assert(glm::clamp(pos, static_cast<int32_t>(-SECTOR_RADIUS), static_cast<int32_t>(SECTOR_RADIUS)) == pos);

  return mBlocks[pos.z + SECTOR_RADIUS][pos.y + SECTOR_RADIUS][pos.x + SECTOR_RADIUS];
}

void Sector::Update(class World *world)
{
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
          static_cast<RenderAgent *>(block->GetFromFullName(StringIntern("RenderAgent")))->Update(
            { world , this, mSectorPosition * static_cast<int32_t>(Sector::SECTOR_SIZE) + pos }
          );
        }
      }
    }
  }

  mRenderSector.Update();
}

RenderSector &Sector::GetRenderSector()
{
  return mRenderSector;
}
