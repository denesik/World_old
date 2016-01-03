// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Mesh.h"



Mesh::Mesh(std::unique_ptr<IRenderMesh> renderMesh)
  : mRenderMesh(std::move(renderMesh))
{

}

Mesh::~Mesh()
{

}

void Mesh::SetVertexSize(size_t size)
{
  mVertexSize = size;
}

void Mesh::Set(const std::vector<float> &vertex, const std::vector<size_t> &index)
{
  mVertex = vertex;
  mIndex = index;
}

void Mesh::Push(const std::vector<float> &vertex, const std::vector<size_t> &index)
{
  mVertex.insert(mVertex.end(), vertex.begin(), vertex.end());
  mIndex.insert(mIndex.end(), index.begin(), index.end());
}

void Mesh::Push(const Mesh &mesh)
{
  assert(mVertexSize == mesh.mVertexSize && "Размеры вершин не совпадают при слиянии мешей.");
  mVertex.insert(mVertex.end(), mesh.mVertex.begin(), mesh.mVertex.end());
  mIndex.insert(mIndex.end(), mesh.mIndex.begin(), mesh.mIndex.end());
}

void Mesh::Release()
{
  mVertex.swap(decltype(mVertex){});
  mIndex.swap(decltype(mIndex){});
}

const std::vector<float> &Mesh::GetVertex() const
{
  return mVertex;
}

const std::vector<size_t> &Mesh::GetIndex() const
{
  return mIndex;
}

void Mesh::SetAttribute(AttributeType type, Attribute attribute)
{
  assert(mRenderMesh != nullptr && "Отсутствует рендер для рисования буфера.");
  mRenderMesh->SetAttribute(type, attribute);
}

void Mesh::Compile()
{
  assert(mRenderMesh != nullptr && "Отсутствует рендер для рисования буфера.");
  mRenderMesh->Compile(mVertex.data(), mVertex.size(), mVertexSize, mIndex.data(), mIndex.size());
}

bool Mesh::IsCompiled()
{
  assert(mRenderMesh != nullptr && "Отсутствует рендер для рисования буфера.");
  return mRenderMesh->IsCompiled();
}

void Mesh::Draw()
{
  assert(mRenderMesh != nullptr && "Отсутствует рендер для рисования буфера.");
  mRenderMesh->Draw();
}

