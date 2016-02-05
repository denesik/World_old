// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderAgent_h__
#define RenderAgent_h__


#include "Agent.h"
#include <memory>
#include "..\Graphic\Render\StaticModel.h"
#include "MeshBlockGenerator.h"


class RenderAgent : public Agent
{
public:
  RenderAgent(GameObject *parent);
  ~RenderAgent();

  void Update(const GameObjectParams &params) override;

  inline MeshBlockGenerator &GetMeshBlockGenerator()
  {
    return mMeshBlockGenerator;
  }

private:
  StaticModel mModel;
  MeshBlockGenerator mMeshBlockGenerator;
};



#endif // RenderAgent_h__
