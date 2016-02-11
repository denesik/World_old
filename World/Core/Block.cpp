#include "Block.h"
#include <memory>
#include "RenderAgent.h"

const StringIntern Block::mRenderAgentName = StringIntern("RenderAgent");

Block::Block()
{
  auto renderAgent = std::make_unique<RenderAgent>(this);
  mAgents[renderAgent->GetFullName()] = std::move(renderAgent);
}
 

Block::~Block()
{
}

PGameObject Block::Clone()
{
  return MakeGameObject<Block>();
}

void Block::Update(GameObjectParams &params)
{
  for (auto &agent : mAgents)
  {
    if (agent.first != mRenderAgentName)
    {
      agent.second->Update(params);
    }
  }
}

void Block::UpdateGraphic(GameObjectParams &params)
{
  for (auto &agent : mAgents)
  {
    if (agent.first == mRenderAgentName)
    {
      agent.second->Update(params);
    }
  }
}