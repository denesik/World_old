// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef agent_cast_h__
#define agent_cast_h__

#include "Agent.h"


template<class T>
T *agent_cast(Agent *agent)
{
  return static_cast<RenderAgent *>(agent);
}


#endif // agent_cast_h__