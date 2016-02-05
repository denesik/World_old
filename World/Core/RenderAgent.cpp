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
  mModelGenerator = std::make_unique<MeshBlockGenerator>();
  mModel.SetTexture(std::get<0>(REGISTRY_GRAPHIC.GetTextureManager().GetTexture("Textures/stone.png")));
}


RenderAgent::~RenderAgent()
{
}

void RenderAgent::Update(const GameObjectParams &params)
{
  if (params.sector->GetRenderSector().IsNeedBuild())
  {
    auto &mg = *static_cast<MeshBlockGenerator *>(GetModelGenerator());
    mg.Enable(MeshBlockGenerator::ALL, true);
    mModel.GetMesh().Release();
    mg.Create(params.pos, mModel.GetMesh());
    params.sector->GetRenderSector().Push(mModel);
  }
}


IMeshGenerator *RenderAgent::GetModelGenerator()
{
  return mModelGenerator.get();
}
