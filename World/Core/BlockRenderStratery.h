// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BlockRenderStratery_h__
#define BlockRenderStratery_h__

#include "IRenderStrategy.h"
#include "MeshBlockGenerator.h"
#include "..\Render\Model.h"


class BlockRenderStratery : public IRenderStrategy
{
public:
  BlockRenderStratery();
  ~BlockRenderStratery();

  const Model &GetModel(const GameObjectParams &params);
  void Load(const rapidjson::Value &val) override;

  MeshBlockGenerator &GetGenerator()
  {
    return mMeshBlockGenerator;
  }

private:
  Model mModel;
  MeshBlockGenerator mMeshBlockGenerator;

};

REGISTER_RENDER_STRATEGY(BlockRenderStratery)

#endif // BlockRenderStratery_h__
