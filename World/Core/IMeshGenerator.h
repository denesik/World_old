// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef IModelGenerator_h__
#define IModelGenerator_h__

#include "..\Graphic\Render\Mesh.h"
#include "..\Graphic\Render\Vertex.h"


class IMeshGenerator
{
public:
  IMeshGenerator() {};
  virtual ~IMeshGenerator() {};

  /// —генерировать меш.
  virtual void Create(const glm::vec3 &pos, Mesh<VertexVT> &mesh) = 0;

};



#endif // IModelGenerator_h__