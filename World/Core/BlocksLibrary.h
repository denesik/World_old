// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BlocksLibrary_h__
#define BlocksLibrary_h__

#include "Block.h"
#include "..\tools\StringIntern.h"
#include <unordered_map>


class BlocksLibrary
{
public:
  BlocksLibrary();
  ~BlocksLibrary();

  void Registry(const StringIntern &name, PBlock block, bool isStatic = true);


  /// Создать блок.
  /// Если блок статический, возвращается указатель на экземпляр блока, хранящийся в библиотеке.
  /// Если блок динамический, создается копия блока.
  /// @param blockId Идентификатор блока.
  PBlock Create(const StringIntern &name);

private:
  std::unordered_map<StringIntern, PBlock> mBlocks;

};



#endif // BlocksLibrary_h__