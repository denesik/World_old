// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef GameObject_h__
#define GameObject_h__

#include "Agent.h"
#include <map>
#include <memory>
#include <functional>


class GameObject
{
public:
  GameObject();
  ~GameObject();

  Agent *GetFromFullName(const StringIntern &name);

private:
  std::map<StringIntern, std::unique_ptr<Agent>> mAgents;

};



#endif // GameObject_h__
