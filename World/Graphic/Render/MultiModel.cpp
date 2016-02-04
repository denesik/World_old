#include "MultiModel.h"
#include "RenderMeshGL1.h"



MultiModel::MultiModel()
{
}


MultiModel::~MultiModel()
{
}

void MultiModel::Push(const Model &model)
{
  mTexture = model.GetTexture();
  if (!mMesh)
  {
    mMesh = std::make_shared<Mesh>(std::make_unique<RenderMeshGL1>());
    mMesh->SetAttribute(ATTRIBUTE_VERTEX, { true, sizeof(VertexVT{}.vertex), offsetof(VertexVT, vertex) });
    mMesh->SetAttribute(ATTRIBUTE_TEXTURE, { true, sizeof(VertexVT{}.texture), offsetof(VertexVT, texture) });
    mMesh->SetVertexSize(sizeof(VertexVT));
	mMesh->Reserve();
    mMesh->Push(*model.GetMesh());
    //mMesh = model.GetMesh();
  }
  else
  {
    mMesh->Push(*model.GetMesh());
  }
}

const PMesh &MultiModel::GetMesh() const noexcept
{
  return mMesh;
}

PMesh &MultiModel::GetMesh() noexcept
{
  return mMesh;
}

const PTexture &MultiModel::GetTexture() const noexcept
{
  return mTexture;
}
