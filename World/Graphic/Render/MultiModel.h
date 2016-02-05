// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef MultiModel_h__
#define MultiModel_h__

#include "Model.h"
#include "RenderableMesh.h"
#include "Vertex.h"


class MultiModel
{
public:
  MultiModel();
  ~MultiModel();

  void Push(Model &model);

//   const PMesh &GetMesh() const noexcept;

  RenderableMesh<VertexVT> &GetMesh() noexcept;

  const PTexture &GetTexture() const noexcept;

private:
  RenderableMesh<VertexVT> mMesh;
  PTexture mTexture;

};



#endif // MultiModel_h__