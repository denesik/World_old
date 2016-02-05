// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef MultiModel_h__
#define MultiModel_h__

#include "StaticModel.h"
#include "RenderableMesh.h"
#include "Vertex.h"


class StaticModelBatch
{
public:
  StaticModelBatch();
  ~StaticModelBatch();

  void Push(StaticModel &model);

  RenderableMesh<VertexVT> &GetMesh() noexcept;

  const PTexture &GetTexture() const noexcept;

private:
  RenderableMesh<VertexVT> mMesh;
  PTexture mTexture;
};



#endif // MultiModel_h__