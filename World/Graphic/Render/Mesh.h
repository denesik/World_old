// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Mesh_h__
#define Mesh_h__

#include <memory>
#include <vector>

template<class V>
class Mesh;

template<class V>
using PMesh = std::shared_ptr<Mesh<V>>;

template<class V>
class Mesh
{
public:
  inline V &Vertex(size_t i)
  {
    return mVertex[i];
  }

  inline size_t &Index(size_t i)
  {
    return mIndex[i];
  }

  inline void Reserve(size_t vertexCount, size_t indexCount)
  {
    mVertex.reserve(vertexCount);
    mIndex.reserve(indexCount);
  }

  inline void Clear()
  {
    mVertex.clear();
    mIndex.clear();
  }

  inline void Release()
  {
    mVertex.swap(decltype(mVertex)());
    mIndex.swap(decltype(mIndex)());
  }

  inline size_t SizeVertex() const
  {
    return mVertex.size();
  }

  inline size_t SizeIndex() const
  {
    return mIndex.size();
  }

  inline void PushVertex(const V &vertex)
  {
    mVertex.push_back(vertex);
  }

  inline void PushIndex(size_t index)
  {
    mIndex.push_back(index);
  }

  inline bool Empty() const noexcept
  {
    return mVertex.empty() && mIndex.empty();
  }

  void Push(const Mesh<V> &mesh)
  {
    mIndex.reserve(mesh.mIndex.size());
    size_t size = mVertex.size();
    for (const auto &i : mesh.mIndex)
    {
      mIndex.push_back(size + i);
    }

    mVertex.insert(mVertex.end(), mesh.mVertex.begin(), mesh.mVertex.end());
  }

protected:
  std::vector<V> mVertex;
  std::vector<size_t> mIndex;
};



#endif // Mesh_h__