// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "GameObject.h"
#include "RenderAgent.h"



GameObject::GameObject()
{
  auto renderAgent = std::make_unique<RenderAgent>(this);
  mAgents[renderAgent->GetFullName()] = std::move(renderAgent);
}


GameObject::~GameObject()
{
}

Agent *GameObject::GetFromFullName(const StringIntern &name)
{
  auto it = mAgents.find(name);
  if (it != mAgents.end())
  {
    return (*it).second.get();
  }

  return nullptr;
}

