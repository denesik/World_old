// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderAgent.h"
#include "Sector.h"

//possibly must be moved into <renderstrats> file
//deserialize autoreg
#include "BlockRenderStratery.h"

RenderAgent::RenderAgent()
  : Agent(nullptr, "RenderAgent", "")
{
}

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

void RenderAgent::jsonLoad(const rapidjson::Value & val)
{
  if (val.HasMember("strategy"))
  {
    const rapidjson::Value &stratVal = val["strategy"];
    if(stratVal.HasMember("type"))
    {
      std::string type = stratVal["type"].GetString();
      std::shared_ptr<IRenderStrategy> irs = RenderStrategyFactory::instance().Create(StringIntern(type));
      irs->jsonLoad(stratVal);
      SetStrategy(irs);
    }
    else
    {
      LOG(error) << "render strategy has no type";
    }
  }
}

void RenderAgent::Update(const GameObjectParams &params)
{
  params.sector->GetRenderSector().Push(mRenderStrategy->Get(params), params.pos);
}

void RenderAgent::SetStrategy(const PRenderStrategy &strategy)
{
  mRenderStrategy = strategy;
}

