// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderMeshGL1.h"

#include <assert.h>
#include <gl/glew.h>
#include "OpenGLCall.h"

RenderMeshGL1::RenderMeshGL1()
{
  for (auto &i : mAttributeState)
  {
    i = { false, 0, 0 };
  }
  GL_CALL(mList = glGenLists(1));
}


RenderMeshGL1::~RenderMeshGL1()
{
  GL_CALL(glDeleteLists(mList, 1));
}

void RenderMeshGL1::SetAttribute(AttributeType type, Attribute attribute)
{
  mAttributeState[type] = attribute;
}

void RenderMeshGL1::Compile(const float *vertex, size_t vertexCount, size_t vertexSize, const size_t *index, size_t indexCount)
{
  assert(vertex && "vertex pointer is null");
  assert(index && "index pointer is null");
  /// Имеется массив вершин и индексов, нужно сформировать дисплейный список.
  /// Для этого нужно перейти к неиндексированному массиву.

  GL_CALL(glNewList(mList, GL_COMPILE));
  GL_CALL(glBegin(GL_TRIANGLES));
  for (size_t i = 0; i < indexCount; ++i)
  {
    if (mAttributeState[ATTRIBUTE_TEXTURE].enabled)
    {
      GL_CALL(glTexCoord2fv(&vertex[(vertexSize * index[i] + mAttributeState[ATTRIBUTE_TEXTURE].offset) / sizeof(float)]));
    }
    if (mAttributeState[ATTRIBUTE_VERTEX].enabled)
    {
      GL_CALL(glVertex3fv(&vertex[(vertexSize * index[i] + mAttributeState[ATTRIBUTE_VERTEX].offset) / sizeof(float)]));
    }
  }
  GL_CALL(glEnd());
  GL_CALL(glEndList());
}

void RenderMeshGL1::Draw()
{
  GL_CALL(glCallList(mList));
}

