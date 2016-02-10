// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RegistryGraphic.h"


#include <iostream>
#include "../Log.h"

RegistryGraphic &RegistryGraphic::Instatce()
{
  static RegistryGraphic registry;
  return registry;
}

RegistryGraphic::RegistryGraphic()
{


  mTextureManager = std::make_unique<TextureManager>();
}

RegistryGraphic::~RegistryGraphic()
{
  mTextureManager.reset();
}



TextureManager &RegistryGraphic::GetTextureManager()
{
  return *mTextureManager;
}

