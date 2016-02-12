// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "IRenderStrategy.h"



RenderStrategyFactory::FactoryType & RenderStrategyFactory::Get()
{
  static FactoryType object;
  return object;
}
