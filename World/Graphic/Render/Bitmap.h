// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#ifndef BITMAP_H
#define BITMAP_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include "Color.h"


class BitmapException : public std::exception
{
public:
  BitmapException(unsigned int id)
    : mId(id)
  {
  }
  virtual const char *what() const throw()
  {
    return "Bitmap exception";
  }

  enum
  {
    FILE_NOT_FOUND,
    FILE_NOT_SAVE,

    COUNT,
  };

private:
  const unsigned int mId;
};

/// Битовое изображение в оперативной памяти.
class Bitmap
{
public:
  /// Создает пустую битмапу.
  Bitmap();

  /// Загружает битмапу из png файла.
  Bitmap(const std::string &fileName);

  /// Создать битмапу заданного размера и цвета.
  Bitmap(const glm::uvec2 &size, const Color &color = Color::black);

  /// Разрушает битмапу.
  ~Bitmap();

  void Set(const glm::uvec2 &pos, Color color);

  Color Get(const glm::uvec2 &pos) const;

  /// Вернуть размер битмапы.
  const glm::uvec2 &GetSize() const;

  /// Вернуть данные битмапы.
  const std::vector<unsigned char> &GetRaw() const;

  /// Сохранить в файл.
  void Save(const std::string &fileName) const;

  /// Вставить битмапу.
  void Insert(const glm::uvec2 &pos, const Bitmap &bitmap);

  /// Зеркалирование.
  /// direction Направление. true - по горизонтали. false - по вертикали.
  void Mirror(bool direction = true);

private:

  std::vector<unsigned char> mData;

  // Размер битмапы.
  glm::uvec2 mSize;

};

#endif // BITMAP_H
