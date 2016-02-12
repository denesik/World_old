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


/// Модель. Имеет всю информацию для рисования.
class Model
{
public:
  enum Type
  {
    Static,
  };

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

  inline Type GetType() const noexcept
  {
    return mType;
  }

private:
  PMesh<VertexVT> mMesh;
  PTexture mTexture;

  Type mType = Static;
};

#endif // Model_h__

