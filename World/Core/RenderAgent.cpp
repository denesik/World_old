// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderAgent.h"
#include "..\Graphic\GameRender\ModelBlockGenerator.h"



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
  return mModelGenerator->Create();
}

IModelGenerator *RenderAgent::GetModelGenerator()
{
  return mModelGenerator.get();
}
