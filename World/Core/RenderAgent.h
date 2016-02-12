// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderAgent_h__
#define RenderAgent_h__


#include "Agent.h"
#include "IRenderStrategy.h"

typedef std::unique_ptr<class RenderAgent> PStaticRenderAgent;

/// Рендер осуществляется с помощью стратегий.
/// Рендер агент управляет стратегиями.
class RenderAgent final : public Agent
{
public:
  RenderAgent();
  RenderAgent(GameObject *parent, const std::string &name = "");
  RenderAgent(const RenderAgent &object, GameObject *parent, const std::string &name = "");
  ~RenderAgent();

  PAgent Clone(GameObject *parent, const std::string &name = "") override;

  void Load(const rapidjson::Value &val) override;

  void Update(const GameObjectParams &params) override;

  void SetStrategy(const PRenderStrategy &strategy);

  inline bool IsStatic() const noexcept
  {
    return mStatic;
  }

private:
  bool mStatic = true;
  PRenderStrategy mRenderStrategy;

};

REGISTER_AGENT(RenderAgent)

#endif // RenderAgent_h__
