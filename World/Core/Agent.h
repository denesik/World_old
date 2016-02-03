// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Agent_h__
#define Agent_h__

#include "..\tools\StringIntern.h"
#include "GameObjectParams.h"

class GameObject;

class Agent
{
public:
  /// Создать агент с указанным типом и именем.
  Agent(GameObject *parent, const std::string &type, const std::string &name = "");
  virtual ~Agent();

  virtual void Update(const GameObjectParams &params) = 0;

  /// Вурнуть имя типа агента.
  const StringIntern &GetTypeName();

  /// Вернуть имя агента указанного типа.
  const StringIntern &GetName();

  /// Вернуть полное имя агента. Включает имя типа и имя агента.
  const StringIntern &GetFullName();

protected:
  GameObject *mParent;

  const StringIntern mTypeName;
  const StringIntern mAgentName;
  const StringIntern mFullName;

};



#endif // Agent_h__