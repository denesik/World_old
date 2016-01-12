// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderAgent.h"
#include "..\Graphic\GameRender\ModelBlockGenerator.h"
#include "GameObject.h"
#include "PositionAgent.h"


RenderAgent::RenderAgent(GameObject *parent)
  : Agent(parent, "RenderAgent")
{
  mModelGenerator = std::make_unique<ModelBlockGenerator>();
}


RenderAgent::~RenderAgent()
{
}

Model RenderAgent::GetModel()
{
  auto &mg = *static_cast<ModelBlockGenerator *>(static_cast<RenderAgent *>(mParent->GetFromFullName(StringIntern("RenderAgent")))->GetModelGenerator());
  mg.SetPosition(static_cast<PositionAgent *>(mParent->GetFromFullName(StringIntern("PositionAgent")))->Get());
  mg.Enable(ModelBlockGenerator::ALL, true);
  return mModelGenerator->Create();
}

IModelGenerator *RenderAgent::GetModelGenerator()
{
  return mModelGenerator.get();
}
