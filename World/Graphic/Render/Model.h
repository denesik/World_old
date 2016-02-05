// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Model_h__
#define Model_h__

#include "Texture.h"
#include "Mesh.h"

class Model
{
public:
  Model(PMesh = nullptr, PTexture = nullptr);
  ~Model();

  //void SetMesh(PMesh mesh);

  void SetTexture(PTexture texture);

  //const PMesh &GetMesh() const noexcept;

  Mesh<VertexVT> &GetMesh() noexcept;

  const PTexture &GetTexture() const noexcept;

private:

  Mesh<VertexVT> mMesh;
  //PMesh mMesh;
  PTexture mTexture;

};

#endif // Model_h__

