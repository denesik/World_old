// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderAgent_h__
#define RenderAgent_h__


#include "Agent.h"
#include <memory>
#include "IMeshGenerator.h"
#include "..\Graphic\Render\StaticModel.h"


class RenderAgent : public Agent
{
public:
  RenderAgent(GameObject *parent);
  ~RenderAgent();

  void Update(const GameObjectParams &params) override;

  IMeshGenerator *GetModelGenerator();

private:
  std::unique_ptr<IMeshGenerator> mModelGenerator;
  StaticModel mModel;

};



#endif // RenderAgent_h__
