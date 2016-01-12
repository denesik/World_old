// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "BlockPositionAgent.h"



BlockPositionAgent::BlockPositionAgent(GameObject *parent)
  : PositionAgent(parent)
{
}


BlockPositionAgent::~BlockPositionAgent()
{
}

const glm::vec3 &BlockPositionAgent::Get() const
{
  return{};
}

void BlockPositionAgent::Set(const glm::vec3 &position)
{

}
