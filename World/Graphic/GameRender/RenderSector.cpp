// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderSector.h"
#include "..\RegistryGraphic.h"



RenderSector::RenderSector()
{
}


RenderSector::~RenderSector()
{
}

void RenderSector::Changed()
{
  mIsChanged = true;
}

bool RenderSector::IsNeedBuild() const
{
  return mIsNeedBuild;
}

void RenderSector::Push(const Model &model)
{
  mModel.Push(model);
}

void RenderSector::Update()
{
  // Рисуем сектор.
  // Если сектор был изменен, ставим флаг, что сектор должен быть перестроен.
  // Если флаг о перестройке установлен - перестраиваем сектор.
  
  if (mIsNeedBuild)
  {
    mModel.GetMesh()->Compile();
    mModel.GetMesh()->Release();

    mIsNeedBuild = false;
  }

  REGISTRY_GRAPHIC.GetRender().Draw(mModel);

  if (mIsChanged)
  {
    mIsNeedBuild = true;
    mIsChanged = false;
  }
}
