// ============================================================================
// ==         Copyright (c) 2016, Samsonov Andrey and Smirnov Denis          ==
// ==                  See license.txt for more information                  ==
// ============================================================================

#pragma once
#ifndef SERIALIZE_H
#define SERIALIZE_H
#include <string>
#include <sstream>
#include <functional>
#include <boost\format.hpp>
#include <glm\glm.hpp>

#include "rapidjson\document.h"

struct NvpHelper {
  template <class T>
  inline static std::pair<const char *, T> make_nvp(const char *name, T &&value) {
    return{ name, std::forward<T>(value) };
  }
};

#define NVP(T) NvpHelper::make_nvp(#T, T)
#define JSONLOAD(...) DeserializeHelper::deserialize(val, __VA_ARGS__)

struct DeserializeHelper {
  static void deserialize(const rapidjson::Value &val)
  {
    (void)val;
  }

  template <typename Last>
  static void deserialize(const rapidjson::Value &val, const Last &last)
  {
    __deserialize(val, last.first, last.second);
  }

  template <typename First, typename... Rest>
  static void deserialize(const rapidjson::Value &val, const First &first, const Rest&... rest)
  {
    __deserialize(val, first.first, first.second);
    deserialize(val, rest...);
  }

private:

  template<typename _Ty>
  static void __deserialize_array_part(const rapidjson::Value &val, _Ty &target)
  {
    target.Deserialize(val);
  }

  template<typename _Ty>
  static void __deserialize_array_part(const rapidjson::Value &arr, std::vector<_Ty> &target)
  {
    if (arr.IsArray())
    {
      for (decltype(arr.Size()) i = 0; i < arr.Size(); i++)
      {
        _Ty part;
        __deserialize_array_part(arr[i], part);
        target.push_back(std::move(part));
      }
    }
  }

  template<typename _Ty>
  static void __deserialize(const rapidjson::Value &val, const char *s, _Ty &target)
  {
    if (!val.HasMember(s))
      throw std::invalid_argument(boost::lexical_cast(::string_format("value has no %s member", s));

    const rapidjson::Value &v = val[s];
    target.Deserialize(v);
  }

  template<typename _Ty>
  static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<_Ty> &target)
  {

    if (val.HasMember(s) && val[s].IsArray())
    {
      const rapidjson::Value &arr = val[s];
      for (decltype(arr.Size()) i = 0; i < arr.Size(); i++)
      {
        _Ty part;
        __deserialize_array_part(arr[i], part);
        target.push_back(std::move(part));
      }
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, int &target)
  {
    if (val.HasMember(s))
    {
      if (!val[s].IsInt())
        throw std::invalid_argument((boost::format("value %1% is not a integer") % s).str());
      target = val[s].GetInt();
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, std::string &target)
  {
    if (val.HasMember(s))
    {
      if (!val[s].IsString())
        throw std::invalid_argument((boost::format("value %1% is not a string") % s).str());
      target = val[s].GetString();
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, float &target)
  {
    if (val.HasMember(s))
    {
      if (!val[s].IsNumber())
        throw std::invalid_argument((boost::format("value %1% is not a number") % s).str());
      target = static_cast<float>(val[s].GetDouble());
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, bool &target)
  {
    if (val.HasMember(s))
    {
      if (!val[s].IsBool_())
        throw std::invalid_argument((boost::format("value %1% is not a bool") % s).str());
      target = val[s].GetBool_();
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, glm::vec2 &target)
  {
    if (val.HasMember(s) && val[s].IsArray())
    {
      const rapidjson::Value &arr = val[s];
      if (arr.Size() != 2)          throw std::invalid_argument((boost::format("value %1% is not vec2"       ) % s).str());
      if (!arr.Begin()->IsNumber()) throw std::invalid_argument((boost::format("value %1%[0] is not a number") % s).str());
      if (!arr[1].IsNumber())       throw std::invalid_argument((boost::format("value %1%[1] is not a number") % s).str());

      target.x = static_cast<float>(arr.Begin()->GetDouble());
      target.y = static_cast<float>(arr[1].GetDouble());
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, glm::vec3 &target)
  {
    if (val.HasMember(s) && val[s].IsArray())
    {
      const rapidjson::Value &arr = val[s];
      if (arr.Size() != 3)          throw std::invalid_argument("value is not vec3");
      if (!arr.Begin()->IsNumber()) throw std::invalid_argument((boost::format("value %1%[0] is not a number") % s).str());
      if (!arr[1].IsNumber())       throw std::invalid_argument((boost::format("value %1%[1] is not a number") % s).str());
      if (!arr[2].IsNumber())       throw std::invalid_argument((boost::format("value %1%[2] is not a number") % s).str());

      target.x = static_cast<float>(arr.Begin()->GetDouble());
      target.y = static_cast<float>(arr[1].GetDouble());
      target.z = static_cast<float>(arr[2].GetDouble());
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, glm::vec4 &target)
  {
    if (val.HasMember(s) && val[s].IsArray())
    {
      const rapidjson::Value &arr = val[s];
      if (arr.Size() != 4)          throw std::invalid_argument("target variable is not vec4");
      if (!arr.Begin()->IsNumber()) throw std::invalid_argument((boost::format("value %1%[0] is not a number") % s).str());
      if (!arr[1].IsNumber())       throw std::invalid_argument((boost::format("value %1%[1] is not a number") % s).str());
      if (!arr[2].IsNumber())       throw std::invalid_argument((boost::format("value %1%[2] is not a number") % s).str());
      if (!arr[3].IsNumber())       throw std::invalid_argument((boost::format("value %1%[3] is not a number") % s).str());

      target.x = static_cast<float>(arr.Begin()->GetDouble());
      target.y = static_cast<float>(arr[1].GetDouble());
      target.z = static_cast<float>(arr[2].GetDouble());
      target.w = static_cast<float>(arr[3].GetDouble());
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<int> &target)
  {
    if (val.HasMember(s))
    {
      const rapidjson::Value &arr = val[s];
      for (decltype(arr.Size()) i = 0; i < arr.Size(); i++)
      {
        if (!arr[i].IsInt())
          throw std::invalid_argument(sge::string_format("value %s[%d] is not a integer", s, i));
        target.push_back(arr[i].GetInt());
      }
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<std::string> &target)
  {
    if (val.HasMember(s) && val[s].IsArray())
    {
      const rapidjson::Value &arr = val[s];
      for (decltype(arr.Size()) i = 0; i < arr.Size(); i++)
      {
        if (!arr[i].IsString())
          throw std::invalid_argument((boost::format("value %1%[%2%] is not a string") % s % i).str());
        target.push_back(arr[i].GetString());
      }
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<bool> &target)
  {
    if (val.HasMember(s) && val[s].IsArray())
    {
      const rapidjson::Value &arr = val[s];
      for (decltype(arr.Size()) i = 0; i < arr.Size(); i++)
      {
        if (!arr[i].IsBool_())
          throw std::invalid_argument((boost::format("value %1%[%2%] is not a bool") % s % i).str());
        target.push_back(arr[i].GetBool_());
      }
    }
  }

  template<>
  static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<float> &target)
  {
    if (val.HasMember(s) && val[s].IsArray())
    {
      const rapidjson::Value &arr = val[s];
      for (decltype(arr.Size()) i = 0; i < arr.Size(); i++)
      {
        if (!arr[i].IsDouble())
          throw std::invalid_argument((boost::format("value %1%[%2%] is not a number") % s % i).str());
        target.push_back(static_cast<float>(arr[i].GetDouble()));
      }
    }
  }
};

#endif // SERIALIZE_H
