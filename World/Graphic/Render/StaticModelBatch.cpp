#include "StaticModelBatch.h"
#include "RenderMeshGL1.h"
#include "..\..\Log.h"

void StaticModelBatch::Push(const StaticModel &model)
{
  if (mMesh.Empty())
  {
    mTexture = model.GetTexture();
  }
  if (mTexture == model.GetTexture())
  {
    mMesh.Push(model.GetMesh());
  }
  else
  {
    LOG(warning) << "Батчинг модели. Текстуры не совпадают.";
  }
}