// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef PositionAgent_h__
#define PositionAgent_h__

#include "Agent.h"
#include <glm/glm.hpp>

class PositionAgent : public Agent
{
public:
  PositionAgent(GameObject *parent);
  ~PositionAgent();

  virtual const glm::vec3 &Get() const = 0;

  virtual void Set(const glm::vec3 &position) = 0;
};



#endif // PositionAgent_h__