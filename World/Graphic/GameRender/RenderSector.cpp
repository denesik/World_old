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

void RenderSector::Push(const Model &model)
{
  mModel.Push(model);
}

void RenderSector::Update()
{
  mModel.GetMesh()->Compile();
  REGISTRY_GRAPHIC.GetRender().Draw(mModel);

  mModel.GetMesh()->Release();
}
