// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Texture.h"
#include <GL/glew.h>
#include "OpenGLCall.h"
#include <exception>

Texture::Texture(const Bitmap &bitmap, bool mip)
  : mTextureId(0), mSize(bitmap.GetSize()), mMip(mip)
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

  if (mip)
  {
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smoothing ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smoothing ? GL_LINEAR_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST));
  }
  else
  {
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smoothing ? GL_LINEAR : GL_NEAREST));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smoothing ? GL_LINEAR : GL_NEAREST));
  }

  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &bitmap.GetRaw()[0]));
}

void Texture::GenMipmap()
{
  if (mMip)
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
  GL_CALL(glDeleteTextures(1, &mTextureId));
}

void Texture::Set(TextureSlot slot)
{
  GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, mTextureId));
}