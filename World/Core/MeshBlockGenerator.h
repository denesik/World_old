// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef ModelBlockGenerator_h__
#define ModelBlockGenerator_h__

#include <array>
#include "..\Render\Mesh.h"
#include "..\Render\Vertex.h"


/// Генератор модели для блока.
/// Меш формируется автоматически, для каждой стороны блока можно указать текстуру.
/// Все текстуры должны находиться в одном текстурном атласе.
/// Для каждой стороны блока можно указать, нужно ли рисовать сторону. 
class MeshBlockGenerator
{
public:
  enum Side
  {
    EMPTY = 0,

    FRONT = 1 << 0,
    RIGHT = 1 << 1,
    BACK = 1 << 2,
    LEFT = 1 << 3,
    TOP = 1 << 4,
    BOTTOM = 1 << 5,

    ALL = 0x3F,
  };

public:
  MeshBlockGenerator();

  void Create(Mesh<VertexVT> &mesh, Side side);

  void SetTexture(int side, std::string texture);

  void Enable(int side, bool enabled);

  void Generate();

  inline const PMesh<VertexVT> &Create(Side side) const
  {
    return mMeshArray[side];
  }

private:
  /// Список координат текстур для сторон куба в атласе.
  std::array<glm::vec4, 6> mTextures;

  std::array<PMesh<VertexVT>, 64> mMeshArray;
};



#endif // ModelBlockGenerator_h__