// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Agent.h"
#include "GameObject.h"



Agent::Agent(GameObject *parent, const StringIntern &type, const StringIntern &name)
  : mParent(parent), mTypeName(type), mAgentName(name), mFullName(mTypeName + mAgentName)
{
}

Agent::~Agent()
{
}

const StringIntern &Agent::GetTypeName()
{
  return mTypeName;
}

const StringIntern &Agent::GetName()
{
  return mAgentName;
}

const StringIntern &Agent::GetFullName()
{
  return mFullName;
}
