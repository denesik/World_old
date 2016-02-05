// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Model_h__
#define Model_h__

#include "Texture.h"
#include "Mesh.h"
#include "Vertex.h"

class StaticModel
{
public:
  StaticModel();
  ~StaticModel();

  void SetTexture(PTexture texture);

  Mesh<VertexVT> &GetMesh() noexcept;

  const PTexture &GetTexture() const noexcept;

private:
  Mesh<VertexVT> mMesh;
  PTexture mTexture;

};

#endif // Model_h__

