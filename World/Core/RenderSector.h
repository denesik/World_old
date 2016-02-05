// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderSector_h__
#define RenderSector_h__

#include "..\Graphic\Render\MultiModel.h"


/// Рисует сектор.
/// Поток логики: Если установлен флаг, пробегаем по всем блокам, запрашиваем рендер агента,
/// у рендер агента запрашиваем модель, сливаем все в один буфер.
/// Поток рендера: Затем компилируем и рисуем.
class RenderSector
{
public:
  RenderSector();
  ~RenderSector();

  /// Сообщить сектору, что его геометрия изменилась.
  void Changed();

  /// Нужно ли перестроить геометрию?
  bool IsNeedBuild() const;

  void Push(const Model &model);

  void Update();

private:
  MultiModel mModel;

  bool mIsChanged = false;
  bool mIsNeedBuild = true;

};



#endif // RenderSector_h__