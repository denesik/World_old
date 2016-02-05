// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "StaticModel.h"




StaticModel::StaticModel()
{
}

StaticModel::~StaticModel()
{
}

void StaticModel::SetTexture(PTexture texture)
{
  mTexture = texture;
}

Mesh<VertexVT> &StaticModel::GetMesh() noexcept
{
  return mMesh;
}

const PTexture &StaticModel::GetTexture() const noexcept
{
  return mTexture;
}
