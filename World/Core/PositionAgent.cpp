// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "PositionAgent.h"



PositionAgent::PositionAgent(GameObject *parent)
  : Agent(parent, "PositionAgent")
{
}


PositionAgent::~PositionAgent()
{
}

PAgent PositionAgent::Clone()
{
  return MakeAgent<PositionAgent>(*this);
}

void PositionAgent::Update(const GameObjectParams &params)
{

}
