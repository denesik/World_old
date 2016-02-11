// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Atlas.h"
#include <iostream>


Atlas::Atlas(const glm::uvec2 &size)
  : mBitmap(size),
    mRoot({0, 0}, size),
    mNodes([](const glm::uvec2 &n1, const glm::uvec2 &n2)
      {
        // Периметр.
        return n1.x + n1.y < 
               n2.x + n2.y;
      })
       
{
  mNodes.insert(std::pair<glm::uvec2, Node *>(mRoot.size, &mRoot));
}


Atlas::~Atlas()
{
}

glm::uvec4 Atlas::Add(const std::string &name, const Bitmap &bitmap)
{
  const auto &size = bitmap.GetSize();
  // Ищем самый маленький контейнер, в который может влезть битмапа.
  for (auto it = mNodes.lower_bound(bitmap.GetSize()); it != mNodes.end(); ++it)
  {
    const auto &nodeSize = (*it).first;
    if (nodeSize.x >= size.x && nodeSize.y >= size.y)
    {
      auto node = (*it).second;
      // Вставляем битмапу.
      mBitmap.Insert(node->pos, bitmap);

      // Разбиваем контейнер на два поменьше.
      if (node->size.x - size.x)
      {
        node->right = new Node(
          {node->pos.x + size.x, node->pos.y},
          {node->size.x - size.x, size.y}
        );
        mNodes.insert(std::pair<glm::uvec2, Node *>(node->right->size, node->right));
      }
      if (node->size.y - size.y)
      {
        node->bottom = new Node(
          {node->pos.x, node->pos.y + size.y},
          {node->size.x, node->size.y - size.y}
        );
        mNodes.insert(std::pair<glm::uvec2, Node *>(node->bottom->size, node->bottom));
      }

      mBitmap.Insert(node->pos, bitmap);
      mNodes.erase(it);
      return { node->pos.x , node->pos.y, size.x, size.y };
    }
  }

  return {};
}

bool Atlas::Remove(const std::string &name)
{
  assert(false); // Заглушка.
  return true;
}

const Bitmap &Atlas::GetAtlas() const
{
  return mBitmap;
}
