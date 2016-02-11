// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef PositionAgent_h__
#define PositionAgent_h__

#include "Agent.h"
#include "..\tools\CoordSystem.h"



using PPositionAgent = std::unique_ptr<class PositionAgent>;

class PositionAgent : public Agent
{
public:
  PositionAgent();
  PositionAgent(GameObject *parent, const std::string &name = "");
  PositionAgent(const PositionAgent &object, GameObject *parent, const std::string &name = "");
  ~PositionAgent();

  PAgent Clone(GameObject *parent, const std::string &name = "") override;

  void jsonLoad(const rapidjson::Value &val) override;

  void Update(const GameObjectParams &params) override;

  inline void Set(const WPos &pos) noexcept
  {
    mPos = pos;
  }

  inline const WPos &Get() const noexcept
  {
    return mPos;
  }

  inline WPos &Get() noexcept
  {
    return mPos;
  }

private:
  WPos mPos;

};

REGISTER_AGENT(PositionAgent)

#endif // PositionAgent_h__