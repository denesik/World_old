// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "DB.h"



DB &DB::Get()
{
  static DB obj;
  return obj;
}

void DB::Registry(const StringIntern &name, PBlock block, bool isStatic)
{
  mBlocks[name] = block;
}

PBlock DB::Create(const StringIntern &name)
{
  return mBlocks[name];
}
