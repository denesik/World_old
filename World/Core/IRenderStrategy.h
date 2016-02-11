// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef IRenderStrategy_h__
#define IRenderStrategy_h__

#include "GameObjectParams.h"
#include "..\Render\StaticModel.h"
#include <memory>

using PRenderStrategy = std::shared_ptr<class IRenderStrategy>;

template<class T, class... Args>
inline std::shared_ptr<T> MakeRenderStrategy(Args&&... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

class IRenderStrategy
{
public:
  IRenderStrategy() {};
  virtual ~IRenderStrategy() {};

  virtual const StaticModel &Get(const GameObjectParams &params) = 0;
};



#endif // IRenderStrategy_h__