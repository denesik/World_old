// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Mesh.h"



MeshOld::MeshOld(std::unique_ptr<IRenderMeshStrategy> renderMesh)
  : mRenderMesh(std::move(renderMesh))
{

}

MeshOld::~MeshOld()
{

}

void MeshOld::SetVertexSize(size_t size)
{
  mVertexSize = size;
}

void MeshOld::Set(const std::vector<float> &vertex, const std::vector<size_t> &index)
{
  mVertex = vertex;
  mIndex = index;
}

void MeshOld::Push(const std::vector<float> &vertex, const std::vector<size_t> &index)
{
  mIndex.reserve(index.size());
  size_t size = mVertex.size() / (mVertexSize / sizeof(float));
  for (const auto &i : index)
  {
    mIndex.push_back(size + i);
  }

  mVertex.insert(mVertex.end(), vertex.begin(), vertex.end());
}

void MeshOld::Push(const MeshOld &mesh)
{
  assert(mVertexSize == mesh.mVertexSize && "Размеры вершин не совпадают при слиянии мешей.");
  mIndex.reserve(mesh.mIndex.size());
  size_t size = mVertex.size() / (mVertexSize / sizeof(float));
  for (const auto &i : mesh.mIndex)
  {
    mIndex.push_back(size + i);
  }

  mVertex.insert(mVertex.end(), mesh.mVertex.begin(), mesh.mVertex.end());
}

void MeshOld::Reserve()
{
	mVertex.reserve(150 * 21 * 21 * 21);
	mIndex.reserve(40 * 21 * 21 * 21);
}

void MeshOld::Release()
{
  mVertex.swap(decltype(mVertex){});
  mIndex.swap(decltype(mIndex){});
}

const std::vector<float> &MeshOld::GetVertex() const
{
  return mVertex;
}

const std::vector<size_t> &MeshOld::GetIndex() const
{
  return mIndex;
}

std::vector<float>& MeshOld::GetVertex()
{
	return mVertex;
}

std::vector<size_t>& MeshOld::GetIndex()
{
	return mIndex;
}

void MeshOld::SetAttribute(AttributeType type, Attribute attribute)
{
  assert(mRenderMesh != nullptr && "Отсутствует рендер для рисования буфера.");
  mRenderMesh->SetAttribute(type, attribute);
}

void MeshOld::Compile()
{
  assert(mRenderMesh != nullptr && "Отсутствует рендер для рисования буфера.");
  mRenderMesh->Compile(mVertex.data(), mVertex.size(), mVertexSize, mIndex.data(), mIndex.size());
}

bool MeshOld::IsCompiled()
{
  assert(mRenderMesh != nullptr && "Отсутствует рендер для рисования буфера.");
  return mRenderMesh->IsCompiled();
}

void MeshOld::Draw()
{
  assert(mRenderMesh != nullptr && "Отсутствует рендер для рисования буфера.");
  mRenderMesh->Draw();
}

