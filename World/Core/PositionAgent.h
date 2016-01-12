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

  const glm::vec3 &Get() const;

  void Set(const glm::vec3 &position);

private:
  glm::vec3 mPosition;

};



#endif // PositionAgent_h__