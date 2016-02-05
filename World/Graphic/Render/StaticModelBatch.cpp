#include "StaticModelBatch.h"
#include "RenderMeshGL1.h"



StaticModelBatch::StaticModelBatch()
{
}


StaticModelBatch::~StaticModelBatch()
{
}

void StaticModelBatch::Push(StaticModel &model)
{
  mTexture = model.GetTexture();
  mMesh.Push(model.GetMesh());
}

RenderableMesh<VertexVT> &StaticModelBatch::GetMesh() noexcept
{
  return mMesh;
}

const PTexture &StaticModelBatch::GetTexture() const noexcept
{
  return mTexture;
}
