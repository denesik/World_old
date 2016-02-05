// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderSector.h"
#include "..\Graphic\RegistryGraphic.h"
#include "..\Log.h"
#include "Sector.h"



RenderSector::RenderSector()
{
  mModel.GetMesh() = std::make_shared<std::remove_reference_t<decltype(mModel.GetMesh())>::element_type>();
  mModel.GetMesh()->Reserve(24 * Sector::SECTOR_SIZE * Sector::SECTOR_SIZE * Sector::SECTOR_SIZE, 
                           36 * Sector::SECTOR_SIZE * Sector::SECTOR_SIZE * Sector::SECTOR_SIZE);
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

void RenderSector::Push(const StaticModel &model, const glm::vec3 &pos)
{
  auto &dst = mModel.GetMesh();
  const auto &src = model.GetMesh();
  if (dst->Empty())
  {
    mModel.SetTexture(model.GetTexture());
  }
  if (mModel.GetTexture() == model.GetTexture())
  {
    size_t size = dst->SizeVertex();
    dst->Push(*src);
    for (size_t i = size; i < dst->SizeVertex(); ++i)
    {
      dst->Vertex(i).vertex += pos;
    }
  }
  else
  {
    LOG(warning) << "Батчинг меша в секторе пропущен. Текстуры не совпадают.";
  }
}

void RenderSector::Update()
{
  // Рисуем сектор.
  // Если сектор был изменен, ставим флаг, что сектор должен быть перестроен.
  // Если флаг о перестройке установлен - перестраиваем сектор.
  
  if (mIsNeedBuild)
  {
    auto currentTime = glfwGetTime();
    mModel.GetMesh()->Compile();
    mModel.GetMesh()->Release();
    LOG(info) << "ListGen: " << glfwGetTime() - currentTime;
    mIsNeedBuild = false;
  }

  REGISTRY_GRAPHIC.GetRender().Draw(mModel);

  if (mIsChanged)
  {
    mModel.GetMesh()->Reserve(24 * Sector::SECTOR_SIZE * Sector::SECTOR_SIZE * Sector::SECTOR_SIZE,
                             36 * Sector::SECTOR_SIZE * Sector::SECTOR_SIZE * Sector::SECTOR_SIZE);

    mIsNeedBuild = true;
    mIsChanged = false;
  }
}
