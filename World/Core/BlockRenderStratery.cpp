// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "BlockRenderStratery.h"
#include "..\Render\TextureManager.h"
#include "Config.h"
#include "Sector.h"
#include "World.h"
#include "..\tools\CoordSystem.h"

BlockRenderStratery::BlockRenderStratery()
{
  mModel.SetTexture(std::get<0>(TextureManager::Get().GetTexture("Textures/stone.png")));
}


BlockRenderStratery::~BlockRenderStratery()
{
}

const Model & BlockRenderStratery::GetModel(const GameObjectParams &params)
{
  if (params.sector->GetRenderSector().IsNeedBuild())
  {
    const int32_t size = static_cast<int32_t>(SECTOR_SIZE);

    size_t sides = MeshBlockGenerator::ALL;
    auto pos = cs::WBtoSB(params.pos, params.sector->GetSectorPosition());
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
      auto pos = static_cast<WBPos>(params.pos);
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
      auto pos = static_cast<WBPos>(params.pos);
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
      auto pos = static_cast<WBPos>(params.pos);
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
      auto pos = static_cast<WBPos>(params.pos);
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
      auto pos = static_cast<WBPos>(params.pos);
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
      auto pos = static_cast<WBPos>(params.pos);
      --pos.z;
      if (params.world->GetBlock(pos))
      {
        sides &= ~MeshBlockGenerator::BOTTOM;
      }
    }

    mModel.GetMesh() = mMeshBlockGenerator.Create(static_cast<MeshBlockGenerator::Side>(sides));
  }

  return mModel;
}

void BlockRenderStratery::Load(const rapidjson::Value & val)
{
  auto &mg = GetGenerator();

  if (val.HasMember("all"))
  {
    mg.SetTexture(MeshBlockGenerator::ALL, val["all"].GetString());
    
  }

  mg.Generate();
}
