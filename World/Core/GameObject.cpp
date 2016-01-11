// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "GameObject.h"
#include "RenderAgent.h"



GameObject::GameObject()
{
  mAgents.push_back(std::make_unique<RenderAgent>(this));
}


GameObject::~GameObject()
{
}

class RenderAgent &GameObject::GetRenderAgent()
{
  return *static_cast<RenderAgent *>(mAgents[0].get());
}
