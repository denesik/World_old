// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef GameObject_h__
#define GameObject_h__

#include "Agent.h"
#include <vector>
#include <memory>


class GameObject
{
public:
  GameObject();
  ~GameObject();

  class RenderAgent &GetRenderAgent();

private:
  std::vector<std::unique_ptr<Agent>> mAgents;

};



#endif // GameObject_h__
