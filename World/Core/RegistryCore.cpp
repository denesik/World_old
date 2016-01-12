// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RegistryCore.h"

RegistryCore &RegistryCore::Instatce()
{
  static RegistryCore registry;
  return registry;
}

BlocksLibrary &RegistryCore::GetBlocksLibrary()
{
  return mBlocksLibrary;
}

World &RegistryCore::GetWorld()
{
  return mWorld;
}

RegistryCore::RegistryCore()
{

}

RegistryCore::~RegistryCore()
{
}


