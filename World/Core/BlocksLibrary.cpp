// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "BlocksLibrary.h"



BlocksLibrary::BlocksLibrary()
{
}


BlocksLibrary::~BlocksLibrary()
{
}

void BlocksLibrary::Registry(const StringIntern &name, PBlock block, bool isStatic)
{
  mBlocks[name] = block;
}

PBlock BlocksLibrary::Create(const StringIntern &name)
{
  return mBlocks[name];
}
