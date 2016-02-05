// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef IModelGenerator_h__
#define IModelGenerator_h__

#include "..\Graphic\Render\Model.h"

class IModelGenerator
{
public:
  IModelGenerator() {};
  virtual ~IModelGenerator() {};

  /// —генерировать модель.
  virtual Model &Create() = 0;

};



#endif // IModelGenerator_h__