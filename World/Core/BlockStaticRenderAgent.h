// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BlockStaticRenderAgent_h__
#define BlockStaticRenderAgent_h__

#include "StaticRenderAgent.h"
#include "..\Graphic\Render\StaticModel.h"
#include "MeshBlockGenerator.h"



using PBlockStaticRenderAgent = std::unique_ptr<class BlockStaticRenderAgent>;

class BlockStaticRenderAgent : public StaticRenderAgent
{
public:
  BlockStaticRenderAgent(GameObject *parent);
  ~BlockStaticRenderAgent();

  PAgent Clone() override;

  void Update(const GameObjectParams &params) override;

  inline MeshBlockGenerator &GetMeshBlockGenerator()
  {
    return mMeshBlockGenerator;
  }
private:
  StaticModel mModel;
  MeshBlockGenerator mMeshBlockGenerator;
};



#endif // BlockStaticRenderAgent_h__
