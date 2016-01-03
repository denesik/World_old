// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Texture.h"
#include <GL/glew.h>
#include "OpenGLCall.h"


Texture::Texture(const Bitmap &bitmap)
  : mTextureId(0), mSize(bitmap.GetSize())
{
  if(!mSize.x || !mSize.y || !IsPow2(mSize.x) || !IsPow2(mSize.y))
  {
    throw "Texture not created. Incorrect size.";
  }

  bool smoothing = false; 

  GL_CALL(glGenTextures(1, &mTextureId));
  if(!mTextureId)
  {
    throw "Texture not created. GL error.";
  }

  GL_CALL(glBindTexture(GL_TEXTURE_2D, mTextureId));
  
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smoothing ? GL_LINEAR : GL_NEAREST));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smoothing ? GL_LINEAR : GL_NEAREST));

  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &bitmap.GetRaw()[0]));
}

Texture::~Texture()
{
  GL_CALL(glDeleteTextures(1, &mTextureId));
}

const glm::uvec2 & Texture::GetSize()
{
  return mSize;
}

void Texture::Set(TextureSlot slot)
{
  GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, mTextureId));
}

