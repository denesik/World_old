// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#include "..\Render\MultiModel.h"
#ifndef RenderSector_h__
#define RenderSector_h__

/// Рисует сектор.
/// Поток логики: Если установлен флаг, пробегаем по всем блокам, запрашиваем рендер агента,
/// у рендер агента запрашиваем модель, сливаем все в один буфер.
/// Поток рендера: Затем компилируем и рисуем.
class RenderSector
{
public:
  RenderSector();
  ~RenderSector();

  void Push(const Model &model);

  void Update();

private:
  MultiModel mModel;

};



#endif // RenderSector_h__