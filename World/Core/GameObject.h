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
#include "GameObjectParams.h"


using PGameObject = std::shared_ptr<class GameObject>;

class GameObject
{
public:
  GameObject();
  virtual ~GameObject();

  virtual void Update(GameObjectParams &params);

  Agent *GetFromFullName(const StringIntern &name);

protected:
  std::map<StringIntern, std::unique_ptr<Agent>> mAgents;

};



#endif // GameObject_h__
