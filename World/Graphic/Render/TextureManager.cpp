// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "TextureManager.h"

#include <iostream>

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}

void TextureManager::LoadTexture(const std::string &name)
{
  LoadTexture(std::initializer_list<std::string>{name});
}


void TextureManager::LoadTexture(const std::initializer_list<std::string> &names)
{
  for (unsigned int i = 0; i < mMultiAtlas.size(); ++i)
  {
    if (LoadToAtlas(i, names))
    {
      // Кажется мы смогли загрузить все текстуры в один атлас.
      return;
    }
  }
  // Мы пытались, но не смоги...
  // Попробуем создать еще один атлас.
  mMultiAtlas.resize(mMultiAtlas.size() + 1);
  if (!LoadToAtlas(mMultiAtlas.size() - 1, names))
  {
    // Ошибка.
    std::cout << "TextureManager. Load texture error." << std::endl;
  }
}

std::tuple<PTexture, glm::uvec4> TextureManager::GetTexture(const std::string &name) const
{
  auto itTexture = mTextures.find(name);
  if (itTexture == mTextures.end())
  {
    // Текстура не найдена.
    return std::make_tuple<PTexture, glm::uvec4>(nullptr, {});
  }

  return std::tuple<PTexture, glm::uvec4>(mMultiAtlas[(*itTexture).second.index].texture, (*itTexture).second.pos);
}

void TextureManager::Compile()
{
  for (unsigned int i = 0; i < mMultiAtlas.size(); ++i)
  {
    mMultiAtlas[i].texture = std::make_shared<Texture>(mMultiAtlas[i].atlas.GetAtlas());
//    mMultiAtlas[i].atlas.GetAtlas().Save("Atlas_" + std::to_string(i) + ".png");
  }
}

bool TextureManager::LoadToAtlas(size_t atlas, const std::initializer_list<std::string> &names)
{
  // TODO: Удаление из атласа, если не смогли вставить.
  for (auto &name : names)
  {
    Bitmap bitmap;
    try
    {
      bitmap = Bitmap(name);
    }
    catch (char *msg)
    {
      std::cout << msg << std::endl;
      continue;
    }
    auto pos = mMultiAtlas[atlas].atlas.Add(name, bitmap);
    mTextures[name] = { atlas, pos };
  }

  return true;
}
