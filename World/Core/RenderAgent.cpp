// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderAgent.h"
#include "Sector.h"

RenderAgent::RenderAgent(GameObject *parent, const std::string &name)
  : Agent(parent, "RenderAgent", name)
{
  
}

RenderAgent::RenderAgent(const RenderAgent &object, GameObject *parent, const std::string &name)
  : Agent(parent, "RenderAgent", name)
{

}

RenderAgent::~RenderAgent()
{
}

PAgent RenderAgent::Clone(GameObject *parent, const std::string &name)
{
  return MakeAgent<RenderAgent>(*this, parent, name);
}

void RenderAgent::Update(const GameObjectParams &params)
{
  params.sector->GetRenderSector().Push(mRenderStrategy->Get(params), params.pos);
}

void RenderAgent::SetStrategy(const PRenderStrategy &strategy)
{
  mRenderStrategy = strategy;
}

