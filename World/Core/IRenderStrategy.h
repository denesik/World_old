// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef IRenderStrategy_h__
#define IRenderStrategy_h__

#include <boost\noncopyable.hpp>
#include "GameObjectParams.h"
#include "..\Render\Model.h"
#include <memory>
#include <rapidjson\document.h>
#include "TemplateFactory.h"
#include "..\tools\StringIntern.h"

using PRenderStrategy = std::shared_ptr<class IRenderStrategy>;

template<class T, class... Args>
inline std::shared_ptr<T> MakeRenderStrategy(Args&&... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

class IRenderStrategy
{
public:
  IRenderStrategy() = default;
  virtual ~IRenderStrategy() {};

  virtual void Load(const rapidjson::Value &val) = 0;

  virtual const Model &GetModel(const GameObjectParams &params) = 0;
};

#define REGISTER_RENDER_STRATEGY(ctype)                                                                 \
namespace                                                                                               \
{                                                                                                       \
RegisterElement<ctype> RegisterElement##ctype(RenderStrategyFactory::Get(), StringIntern(#ctype)); \
}

struct RenderStrategyFactory : public boost::noncopyable
{
  using FactoryType = TemplateFactory<StringIntern, IRenderStrategy>;
  static FactoryType &Get();
};

#endif // IRenderStrategy_h__