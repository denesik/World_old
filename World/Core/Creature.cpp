// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Creature.h"
#include "agent_cast.h"
#include "PhysicAgent.h"


const StringIntern Creature::mPositionAgentName = StringIntern("PositionAgent");


Creature::Creature()
{
  auto positionAgent = std::make_unique<PositionAgent>(this);
  mAgents[positionAgent->GetFullName()] = std::move(positionAgent);
  auto physicAgent = std::make_unique<PhysicAgent>(this);
  mAgents[physicAgent->GetFullName()] = std::move(physicAgent);
}


Creature::~Creature()
{
}

void Creature::Update(GameObjectParams &params)
{
  params.pos = GetFromFullName<PositionAgent>(mPositionAgentName)->Get();
  GameObject::Update(params);
}
