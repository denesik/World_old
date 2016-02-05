#include "MultiModel.h"
#include "RenderMeshGL1.h"



MultiModel::MultiModel()
{
}


MultiModel::~MultiModel()
{
}

void MultiModel::Push(Model &model)
{
  mTexture = model.GetTexture();
  mMesh.Push(model.GetMesh());
}

// const PMesh &MultiModel::GetMesh() const noexcept
// {
//   return mMesh;
// }
// 
RenderableMesh<VertexVT> &MultiModel::GetMesh() noexcept
{
  return mMesh;
}

const PTexture &MultiModel::GetTexture() const noexcept
{
  return mTexture;
}
