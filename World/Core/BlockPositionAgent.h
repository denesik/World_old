// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BlockPositionAgent_h__
#define BlockPositionAgent_h__

#include "PositionAgent.h"

/// —прашиваем у сектора координаты текущего блока.
class BlockPositionAgent : public PositionAgent
{
public:
  BlockPositionAgent(GameObject *parent);
  ~BlockPositionAgent();

  const glm::vec3 &Get() const override;
  
  void Set(const glm::vec3 &position) override;

};



#endif // BlockPositionAgent_h__