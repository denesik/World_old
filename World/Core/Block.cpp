#include "Block.h"
#include "StaticRenderAgent.h"
#include <memory>
#include "BlockStaticRenderAgent.h"

const StringIntern Block::mRenderAgentName = StringIntern("StaticRenderAgent");

Block::Block()
{
  auto renderAgent = std::make_unique<BlockStaticRenderAgent>(this);
  mAgents[renderAgent->GetFullName()] = std::move(renderAgent);
}
 

Block::~Block()
{
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