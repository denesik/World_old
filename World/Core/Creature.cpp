// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Creature.h"



Creature::Creature()
{
  auto positionAgent = std::make_unique<PositionAgent>(this);
  mAgents[positionAgent->GetFullName()] = std::move(positionAgent);
  mPositionAgent = positionAgent.get();
}


Creature::~Creature()
{
}

void Creature::Update(GameObjectParams &params)
{
  params.pos = mPositionAgent->Get();
  GameObject::Update(params);
}
