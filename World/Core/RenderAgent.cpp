// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderAgent.h"
#include "GameObject.h"
#include "Sector.h"
#include "MeshBlockGenerator.h"
#include "..\Graphic\RegistryGraphic.h"

RenderAgent::RenderAgent(GameObject *parent)
  : Agent(parent, "RenderAgent")
{
  mModel.SetTexture(std::get<0>(REGISTRY_GRAPHIC.GetTextureManager().GetTexture("Textures/stone.png")));
}


RenderAgent::~RenderAgent()
{
}

void RenderAgent::Update(const GameObjectParams &params)
{
  if (params.sector->GetRenderSector().IsNeedBuild())
  {
    mModel.GetMesh().Clear();
    mMeshBlockGenerator.Create(mModel.GetMesh(), params.pos, MeshBlockGenerator::ALL);
    params.sector->GetRenderSector().Push(mModel);
  }
}
