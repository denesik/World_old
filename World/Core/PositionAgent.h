// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef PositionAgent_h__
#define PositionAgent_h__

#include "Agent.h"


class PositionAgent : public Agent
{
public:
  PositionAgent(GameObject *parent);
  ~PositionAgent();

  void Update(const GameObjectParams &params) override;

  inline void Set(const glm::vec3 &pos) noexcept
  {
    mPos = pos;
  }

  inline const glm::vec3 &Get() const noexcept
  {
    return mPos;
  }

  inline glm::vec3 &Get() noexcept
  {
    return mPos;
  }

private:
  glm::vec3 mPos;

};



#endif // PositionAgent_h__