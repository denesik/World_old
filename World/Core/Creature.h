// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Creature_h__
#define Creature_h__

#include "GameObject.h"
#include "PositionAgent.h"

/// Сущность. Имеет позицию.
class Creature : public GameObject
{
public:
  Creature();
  ~Creature();

  void Update(GameObjectParams &params) override;


private:
  static const StringIntern mPositionAgentName;

};



#endif // Creature_h__