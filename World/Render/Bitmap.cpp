// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Bitmap.h"

#include <map>
#include "..\lodepng\lodepng.h"


Bitmap::Bitmap()
{
}

Bitmap::Bitmap(const std::string &fileName)
{
  unsigned error = lodepng::decode(mData, mSize.x, mSize.y, fileName);

  Mirror();

  if(error)
  {
    throw new BitmapException(BitmapException::FILE_NOT_FOUND);
  }
}

Bitmap::Bitmap(const glm::uvec2 &size, const Color &color)
  : mSize(size)
{
  mData.resize(mSize.x * mSize.y * sizeof(color));
  for (decltype(mData.size()) i = 0; i < mData.size(); i += sizeof(color))
  {
    memcpy(&mData[i], &color, sizeof(color));
  }
}

Bitmap::~Bitmap()
{
}

const glm::uvec2 &Bitmap::GetSize() const
{
  return mSize;
}

const std::vector<unsigned char> &Bitmap::GetRaw() const
{
  return mData;
}

void Bitmap::Save(const std::string &fileName) const
{
  Bitmap tmp(*this);
  tmp.Mirror();
  unsigned error = lodepng::encode(fileName, tmp.mData, tmp.mSize.x, tmp.mSize.y);

  if(error)
  {
    throw new BitmapException(BitmapException::FILE_NOT_SAVE);
  }
}


void Bitmap::Insert(const glm::uvec2 &pos, const Bitmap &bitmap)
{
  // Вставляемая битмапа должна полностью влазить в текущую.
  //assert(); 

  const auto &bSize = bitmap.GetSize();

  glm::uvec2 iPos;
  for (; iPos.y < bSize.y; ++iPos.y)
  {
    for (; iPos.x < bSize.x; ++iPos.x)
    {
      Set(pos + iPos, bitmap.Get(iPos));
    }
    iPos.x = 0;
  }

}

void Bitmap::Mirror(bool direction)
{
  if (direction)
  {
    for (unsigned int y = 0; y < mSize.y / 2; ++y)
    {
      // Берем первую строку и меняем с последней.
      // Строка посередине не должна копировать сама себя.
      for (unsigned int x = 0; x < mSize.x * sizeof(Color); ++x)
      {
        std::swap(mData[y * mSize.x * sizeof(Color) + x], 
          mData[(mSize.y - 1 - y) * mSize.x * sizeof(Color) + x]);
      }
    }
  }
  else
  {
    for (unsigned int x = 0; x < mSize.x / 2; ++x)
    {
      for (unsigned int y = 0; y < mSize.y; ++y)
      {
        for (unsigned int k = 0; k < sizeof(Color); ++k)
        {
          std::swap(mData[y * mSize.x * sizeof(Color) + x * sizeof(Color) + k],
            mData[y * mSize.x * sizeof(Color) + (mSize.x - 1 - x) * sizeof(Color) + k]);
        }
      }
    }
  }
}

void Bitmap::Set(const glm::uvec2 &pos, Color color)
{
  memcpy(&mData[pos.y * mSize.x * sizeof(color) + pos.x * sizeof(color)], &color.raw.abgr, sizeof(color));
}

Color Bitmap::Get(const glm::uvec2 &pos) const
{
  Color color;
  memcpy(&color.raw.abgr, &mData[pos.y * mSize.x * sizeof(color) + pos.x * sizeof(color)], sizeof(color));
  return color;
}
