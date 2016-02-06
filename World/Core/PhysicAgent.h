// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef PhysicAgent_h__
#define PhysicAgent_h__

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Agent.h"
#include "GameObject.h"


class PhysicAgent : public Agent
{
public:
  PhysicAgent(GameObject *parent);
  ~PhysicAgent();

  void Update(const GameObjectParams &params) override;

  inline const glm::mat3 &GetDirection() const noexcept
  {
    return mDirection;
  }

  void SetPos(const glm::vec3 &pos);

  const glm::vec3 &GetPos() const;

  /// Повернуть камеру относительно текущей ориентации на заданный угол по трем осям.
  void Rotate(const glm::vec3 &degrees);

  /// Переместиться, относительно текущего положения и ориентации.
  void Move(const glm::vec3 &dist);

private:
  static const StringIntern mPositionAgentName;

  glm::mat3 mDirection;

  glm::quat mQuat;

  glm::vec3 mDir;

};



#endif // PhysicAgent_h__