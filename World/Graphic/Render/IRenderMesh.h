// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef IRenderMesh_h__
#define IRenderMesh_h__

#include "Vertex.h"

class IRenderMesh
{
public:
  virtual ~IRenderMesh() {};

  /// Настроить и включить атрибут.
  /// Для каждого типа атрибута определена фиксированная локация, 
  /// из которой шейдер будет брать поток данных.
  /// Attribute::size размер атрибута в байтах.
  /// Attribute::offset смещение атрибута в байтах.
  /// Attribute::enabled включить или выключить атрибут.
  virtual void SetAttribute(AttributeType type, Attribute attribute) = 0;

  /// Создать сетку в видеопамяти.
  /// @param vertex указатель на начало буфера вершин.
  /// @param vertexSize количество элементов в буфере вершин.
  /// @param index указатель на начало буфера индексов.
  /// @param indexSize количество элементов в буфере индексов.
  virtual void Compile(const float *vertex, size_t vertexCount, size_t vertexSize, const size_t *index, size_t indexCount) = 0;

  /// Скомпилирован ли буфер.
  virtual bool IsCompiled() = 0;

  /// Нарисовать сетку.
  virtual void Draw() = 0;

};


#endif // IRenderMesh_h__