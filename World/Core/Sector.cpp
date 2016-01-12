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


Sector::Sector()
{
  for (mCurrentBlockPosition.z = -SECTOR_RADIUS; mCurrentBlockPosition.z <= SECTOR_RADIUS; ++mCurrentBlockPosition.z)
  {
    for (mCurrentBlockPosition.y = -SECTOR_RADIUS; mCurrentBlockPosition.y <= SECTOR_RADIUS; ++mCurrentBlockPosition.y)
    {
      for (mCurrentBlockPosition.x = -SECTOR_RADIUS; mCurrentBlockPosition.x <= SECTOR_RADIUS; ++mCurrentBlockPosition.x)
      {
        auto &block = mBlocks[mCurrentBlockPosition.z + SECTOR_RADIUS]
          [mCurrentBlockPosition.y + SECTOR_RADIUS]
        [mCurrentBlockPosition.x + SECTOR_RADIUS];

        if (mCurrentBlockPosition.z == 0)
        {
          block = std::make_shared<GameObject>();

          auto &mg = *static_cast<ModelBlockGenerator *>(static_cast<RenderAgent *>(block->GetFromFullName(StringIntern("RenderAgent")))->GetModelGenerator());

          mg.SetTexture(ModelBlockGenerator::ALL, mCurrentBlockPosition.x % 2 ? "Textures/sand.png" : "Textures/stone.png");
          mg.Enable(ModelBlockGenerator::ALL, true);
          mg.SetPosition(mCurrentBlockPosition);
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

const glm::ivec3 & Sector::GetCurrentBlockPosition() const
{
  return mCurrentBlockPosition;
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

void Sector::Update()
{
  MultiModel model;

  for (mCurrentBlockPosition.z = -SECTOR_RADIUS; mCurrentBlockPosition.z <= SECTOR_RADIUS; ++mCurrentBlockPosition.z)
  {
    for (mCurrentBlockPosition.y = -SECTOR_RADIUS; mCurrentBlockPosition.y <= SECTOR_RADIUS; ++mCurrentBlockPosition.y)
    {
      for (mCurrentBlockPosition.x = -SECTOR_RADIUS; mCurrentBlockPosition.x <= SECTOR_RADIUS; ++mCurrentBlockPosition.x)
      {
        auto &block = mBlocks[mCurrentBlockPosition.z + SECTOR_RADIUS]
          [mCurrentBlockPosition.y + SECTOR_RADIUS]
        [mCurrentBlockPosition.x + SECTOR_RADIUS];

        if (block)
        {
          model.Push(static_cast<RenderAgent *>(block->GetFromFullName(StringIntern("RenderAgent")))->GetModel());
        }
      }
    }
  }

  model.GetMesh()->Compile();
  REGISTRY_GRAPHIC.GetRender().Draw(model);
}
