// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef GameObject_h__
#define GameObject_h__

#include <map>
#include <memory>
#include "agent_cast.h"


using PGameObject = std::shared_ptr<class GameObject>;

class GameObject
{
public:
  GameObject();
  virtual ~GameObject();

  virtual void Update(GameObjectParams &params);

  Agent *GetFromFullName(const StringIntern &name);

  template<class T>
  T *GetFromFullName(const StringIntern &name)
  {
    return agent_cast<T>(GetFromFullName(name));
  }

  const Agent *GetFromFullName(const StringIntern &name) const;

  template<class T>
  const T *GetFromFullName(const StringIntern &name) const
  {
    return agent_const_cast<T>(GetFromFullName(name));
  }

protected:
  std::map<StringIntern, std::unique_ptr<Agent>> mAgents;

};



#endif // GameObject_h__
