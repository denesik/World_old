// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderAgent_h__
#define RenderAgent_h__


#include "Agent.h"



using PStaticRenderAgent = std::unique_ptr<class StaticRenderAgent>;

class StaticRenderAgent : public Agent
{
public:
  StaticRenderAgent(GameObject *parent, const std::string &name = "");
  ~StaticRenderAgent();
};



#endif // RenderAgent_h__
