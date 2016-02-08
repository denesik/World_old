// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef TextureManager_h__
#define TextureManager_h__

#include "Texture.h"
#include <string>
#include <unordered_map>
#include "Atlas.h"


/// Менеджер текстур.
/// Хранит все игровые текстуры.
class TextureManager
{
public:
  TextureManager(void);
  ~TextureManager(void);

  /// Загрузить указанную текстуру.
  void LoadTexture(const std::string &name);

  /// Загрузить набор текстур.
  /// Все текстуры будут добавлены в один текстурный атлас.
  void LoadTexture(const std::initializer_list<std::string> &names);

  /// Получить текстуру по имени.
  /// Если текстуры не существует, возвращается нулевой указатель.
  std::tuple<PTexture, glm::uvec4> GetTexture(const std::string &name) const;

  /// Создает текстуры в графической памяти.
  void Compile();

private:

  struct AtlasChunk
  {
    size_t index; // Номер атласа.
    glm::uvec4 pos;     // Положение в атласе.
  };

  struct AtlasTexture
  {
    AtlasTexture()
      : atlas({ 64, 64 })
    {};
    Atlas atlas;
    PTexture texture;
  };

  std::vector<AtlasTexture> mMultiAtlas;

  std::unordered_map<std::string, AtlasChunk> mTextures;

private:

  bool LoadToAtlas(size_t atlas, const std::initializer_list<std::string> &names);

};



#endif // TextureManager_h__
