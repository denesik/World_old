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
  inline void SetTexture(PTexture texture)
  {
    mTexture = texture;
  }

  inline PMesh<VertexVT> &GetMesh() noexcept
  {
    return mMesh;
  }

  inline const PMesh<VertexVT> &GetMesh() const noexcept
  {
    return mMesh;
  }

  inline const PTexture &GetTexture() const noexcept
  {
    return mTexture;
  }

private:
  PMesh<VertexVT> mMesh;
  PTexture mTexture;
};

#endif // Model_h__

