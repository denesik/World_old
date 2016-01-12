// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RegistryCore_h__
#define RegistryCore_h__

#include "BlocksLibrary.h"
#include "World.h"


#define REGISTRY_CORE RegistryCore::Instatce()

class RegistryCore
{
public:
  static RegistryCore &Instatce();

  BlocksLibrary &GetBlocksLibrary();

  World &GetWorld();

private:
  RegistryCore();
  ~RegistryCore();
  RegistryCore(const RegistryCore &);
  RegistryCore& operator=(const RegistryCore &) = delete;

private:

  BlocksLibrary mBlocksLibrary;

  World mWorld;
};

#endif // RegistryCore_h__
