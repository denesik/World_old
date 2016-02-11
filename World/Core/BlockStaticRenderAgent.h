// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BlockStaticRenderAgent_h__
#define BlockStaticRenderAgent_h__

#include "StaticRenderAgent.h"
#include "..\Render\StaticModel.h"
#include "MeshBlockGenerator.h"



using PBlockStaticRenderAgent = std::unique_ptr<class BlockStaticRenderAgent>;

class BlockStaticRenderAgent : public StaticRenderAgent
{
public:
  BlockStaticRenderAgent(GameObject *parent, const std::string &name = "");
  BlockStaticRenderAgent(const BlockStaticRenderAgent &object, GameObject *parent, const std::string &name = "");
  ~BlockStaticRenderAgent();

  PAgent Clone(GameObject *parent, const std::string &name = "") override;

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
