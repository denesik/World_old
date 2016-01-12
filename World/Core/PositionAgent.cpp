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

const glm::vec3 & PositionAgent::Get() const
{
  return mPosition;
}

void PositionAgent::Set(const glm::vec3 &position)
{
  mPosition = position;
}
