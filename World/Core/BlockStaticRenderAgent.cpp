// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "BlockStaticRenderAgent.h"
#include "World.h"
#include "..\Graphic\RegistryGraphic.h"


BlockStaticRenderAgent::BlockStaticRenderAgent(GameObject *parent, const std::string &name)
  : StaticRenderAgent(parent, name)
{
  mModel.SetTexture(std::get<0>(REGISTRY_GRAPHIC.GetTextureManager().GetTexture("Textures/stone.png")));
}


BlockStaticRenderAgent::BlockStaticRenderAgent(const BlockStaticRenderAgent &object, GameObject *parent, const std::string &name)
  : StaticRenderAgent(parent, name)
{

}

BlockStaticRenderAgent::~BlockStaticRenderAgent()
{
}

PAgent BlockStaticRenderAgent::Clone(GameObject *parent, const std::string &name)
{
  return MakeAgent<BlockStaticRenderAgent>(*this, parent, name);
}

void BlockStaticRenderAgent::Update(const GameObjectParams &params)
{
  if (params.sector->GetRenderSector().IsNeedBuild())
  {
    const int32_t size = static_cast<int32_t>(Sector::SECTOR_SIZE);

    size_t sides = MeshBlockGenerator::ALL;
    auto pos = static_cast<glm::ivec3>(params.pos) - params.sector->GetSectorPosition() * size;
    if (pos.x < size - 1)
    {
      ++pos.x;
      if (params.sector->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::RIGHT;
      }
      --pos.x;
    }
    else
    {
      auto pos = static_cast<glm::ivec3>(params.pos);
      ++pos.x;
      if (params.world->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::RIGHT;
      }
    }
    if (pos.x > 0)
    {
      --pos.x;
      if (params.sector->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::LEFT;
      }
      ++pos.x;
    }
    else
    {
      auto pos = static_cast<glm::ivec3>(params.pos);
      --pos.x;
      if (params.world->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::LEFT;
      }
    }

    if (pos.y < size - 1)
    {
      ++pos.y;
      if (params.sector->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::BACK;
      }
      --pos.y;
    }
    else
    {
      auto pos = static_cast<glm::ivec3>(params.pos);
      ++pos.y;
      if (params.world->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::BACK;
      }
    }
    if (pos.y > 0)
    {
      --pos.y;
      if (params.sector->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::FRONT;
      }
      ++pos.y;
    }
    else
    {
      auto pos = static_cast<glm::ivec3>(params.pos);
      --pos.y;
      if (params.world->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::FRONT;
      }
    }

    if (pos.z < size - 1)
    {
      ++pos.z;
      if (params.sector->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::TOP;
      }
      --pos.z;
    }
    else
    {
      auto pos = static_cast<glm::ivec3>(params.pos);
      ++pos.z;
      if (params.world->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::TOP;
      }
    }
    if (pos.z > 0)
    {
      --pos.z;
      if (params.sector->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::BOTTOM;
      }
      ++pos.z;
    }
    else
    {
      auto pos = static_cast<glm::ivec3>(params.pos);
      --pos.z;
      if (params.world->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::BOTTOM;
      }
    }

    if (sides)
    {
      mModel.GetMesh() = mMeshBlockGenerator.Create(static_cast<MeshBlockGenerator::Side>(sides));
      params.sector->GetRenderSector().Push(mModel, params.pos);
    }
  }
}
