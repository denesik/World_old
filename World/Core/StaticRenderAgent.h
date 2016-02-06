// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderAgent_h__
#define RenderAgent_h__


#include "Agent.h"



class StaticRenderAgent : public Agent
{
public:
  StaticRenderAgent(GameObject *parent);
  ~StaticRenderAgent();
};



#endif // RenderAgent_h__
