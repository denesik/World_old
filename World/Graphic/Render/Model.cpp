// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Model.h"




Model::Model(PMesh mesh, PTexture texture)
  : mMesh(mesh), mTexture(texture)
{
}

Model::~Model()
{
}

void Model::SetMesh(PMesh mesh)
{
  mMesh = mesh;
}

void Model::SetTexture(PTexture texture)
{
  mTexture = texture;
}

const PMesh &Model::GetMesh() const noexcept
{
  return mMesh;
}

PMesh &Model::GetMesh() noexcept
{
  return mMesh;
}

const PTexture &Model::GetTexture() const noexcept
{
  return mTexture;
}
