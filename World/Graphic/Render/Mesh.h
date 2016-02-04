// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Mesh_h__
#define Mesh_h__

#include "IRenderMesh.h"
#include <memory>
#include <vector>

typedef std::shared_ptr<class Mesh> PMesh;

class Mesh
{
public:
  Mesh(std::unique_ptr<IRenderMesh> renderMesh = nullptr);
  ~Mesh();

  /// Установить размер вершины в байтах.
  void SetVertexSize(size_t size);

  /// Установить данные вершинного и индексного буфера в ОЗУ.
  void Set(const std::vector<float> &vertex, const std::vector<size_t> &index);

  /// Добавить данные вершинного и индексного буфера в конец буферов.
  void Push(const std::vector<float> &vertex, const std::vector<size_t> &index);

  void Push(const Mesh &mesh);

  void Reserve();

  /// Очистить данные вершинного и индексного буфера.
  void Release();

  /// Вернуть вершинный буфер.
  const std::vector<float> &GetVertex() const;

  /// Вернуть индексный буфер.
  const std::vector<size_t> &GetIndex() const;

  std::vector<float> &GetVertex();

  std::vector<size_t> &GetIndex();

  void SetAttribute(AttributeType type, Attribute attribute);

  void Compile();

  bool IsCompiled();

  void Draw();

private:
  std::unique_ptr<IRenderMesh> mRenderMesh;

  std::vector<float> mVertex;
  std::vector<size_t> mIndex;

  size_t mVertexSize = 0;
};



#endif // Mesh_h__