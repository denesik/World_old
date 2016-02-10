// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once

#ifndef RegistryGraphic_h__
#define RegistryGraphic_h__

#include <memory>
#include "Render/TextureManager.h"


#define REGISTRY_GRAPHIC RegistryGraphic::Instatce()

class RegistryGraphic
{
public:
  static RegistryGraphic &Instatce();

  TextureManager &GetTextureManager();

private:
  RegistryGraphic();
  ~RegistryGraphic();
  RegistryGraphic(const RegistryGraphic &);
  RegistryGraphic& operator=(const RegistryGraphic &);

private:
  std::unique_ptr<TextureManager> mTextureManager;
};

#endif // RegistryGraphic_h__
