// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderSector.h"
#include "..\Graphic\RegistryGraphic.h"
#include "..\Log.h"



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

void RenderSector::Push(Model &model)
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
    auto currentTime = glfwGetTime();
    mModel.GetMesh().Compile();
    LOG(info) << "ListGen: " << glfwGetTime() - currentTime;
    mIsNeedBuild = false;
  }

  REGISTRY_GRAPHIC.GetRender().Draw(mModel);

  if (mIsChanged)
  {
    mIsNeedBuild = true;
    mIsChanged = false;
  }
}
