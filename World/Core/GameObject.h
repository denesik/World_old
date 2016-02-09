// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef GameObject_h__
#define GameObject_h__

#include <map>
#include <memory>
#include <type_traits>
#include "GameObjectParams.h"
#include "Agent.h"
#include "..\tools\StringIntern.h"


using PGameObject = std::shared_ptr<class GameObject>;

template<class T, class... Args>
inline std::shared_ptr<T> MakeGameObject(Args&&... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}


class GameObject
{
public:
  GameObject();
  virtual ~GameObject();

  virtual void Update(GameObjectParams &params);

  virtual PGameObject Clone() = 0;

  Agent *GetFromFullName(const StringIntern &name);

  const Agent *GetFromFullName(const StringIntern &name) const;

  template<class T>
  T *GetFromFullName(const StringIntern &name)
  {
    return static_cast<T*>(GetFromFullName(name));
  }

  template<class T>
  const T *GetFromFullName(const StringIntern &name) const
  {
    return static_cast<const T*>(GetFromFullName(name));
  }

protected:
  std::map<StringIntern, PAgent> mAgents;

};



#endif // GameObject_h__
