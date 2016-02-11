// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef IRenderStrategy_h__
#define IRenderStrategy_h__

#include <boost\noncopyable.hpp>
#include "GameObjectParams.h"
#include "..\Render\StaticModel.h"
#include <memory>
#include <rapidjson\document.h>
#include "..\TemplateFactory.h"
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
  IRenderStrategy() {};
  virtual ~IRenderStrategy() {};
  virtual void jsonLoad(const rapidjson::Value &val) {};

  virtual const StaticModel &Get(const GameObjectParams &params) = 0;
};

#define REGISTER_RENDER_STRATEGY(ctype)                                                                 \
namespace                                                                                               \
{                                                                                                       \
RegisterElement<ctype> RegisterElement##ctype(RenderStrategyFactory::instance(), StringIntern(#ctype)); \
}

struct RenderStrategyFactory : public boost::noncopyable
{
  static TemplateFactory<StringIntern, IRenderStrategy> &instance()
  {
    typedef TemplateFactory<StringIntern, IRenderStrategy> OfType;
    static auto af = std::unique_ptr<OfType>(new OfType());

    return *af;
  }
};

#endif // IRenderStrategy_h__