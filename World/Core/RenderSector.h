// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderSector_h__
#define RenderSector_h__

#include "..\Graphic\Render\DinamicModel.h"
#include <atomic>


/// Рисует сектор.
/// Поток логики: Если установлен флаг, пробегаем по всем блокам, запрашиваем рендер агента,
/// у рендер агента запрашиваем модель, сливаем все в один буфер.
/// Поток рендера: Затем компилируем и рисуем.
class RenderSector
{
public:
  RenderSector();
  ~RenderSector();

  /// Сообщить, что геометрия изменилась.
  void Changed();

  /// Нужно ли перестроить геометрию?
  bool IsNeedBuild() const;

  void Push(const StaticModel &model, const glm::vec3 &pos);

  void Update();

  void Draw();

private:
  DinamicModel mModel;

  bool mIsChanged = true;
  bool mIsNeedBuild = false;

  std::atomic<bool> mRebuildBuffers = false;

};



#endif // RenderSector_h__