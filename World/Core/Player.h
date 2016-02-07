// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Player_h__
#define Player_h__

#include "Creature.h"


class Player : public Creature
{
public:
  Player();
  ~Player();

  /// Повернуть камеру относительно текущей ориентации на заданный угол по трем осям.
  void Rotate(const glm::vec3 &degrees);

  /// Переместиться, относительно текущего положения и ориентации.
  void Move(const glm::vec3 &dist);

  const glm::vec3 &GetPosition() const;

  void SetPosition(const glm::vec3 &pos);

private:
  static const StringIntern mPhysicAgentName;

};



#endif // Player_h__

