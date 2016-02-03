// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderAgent.h"
#include "..\Graphic\GameRender\ModelBlockGenerator.h"
#include "GameObject.h"
#include "Sector.h"

RenderAgent::RenderAgent(GameObject *parent)
  : Agent(parent, "RenderAgent")
{
  mModelGenerator = std::make_unique<ModelBlockGenerator>();
}


RenderAgent::~RenderAgent()
{
}

void RenderAgent::Update(const GameObjectParams &params)
{
  auto &mg = *static_cast<ModelBlockGenerator *>(GetModelGenerator());
  mg.SetPosition(params.pos);
  mg.Enable(ModelBlockGenerator::ALL, true);
  params.sector->GetRenderSector().Push(mg.Create());
}


IModelGenerator *RenderAgent::GetModelGenerator()
{
  return mModelGenerator.get();
}
