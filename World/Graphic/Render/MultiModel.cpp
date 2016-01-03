#include "MultiModel.h"



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
    mMesh = model.GetMesh();
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
