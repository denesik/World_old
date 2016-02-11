// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef VertexTools_h__
#define VertexTools_h__

#include <boost/preprocessor.hpp>


#define __VERTEX_SEQ_TUPLE(seq) BOOST_PP_CAT(__VERTEX_SEQ_TUPLE_X seq, 0)
#define __VERTEX_SEQ_TUPLE_X(x, y, z) ((x, y, z)) __VERTEX_SEQ_TUPLE_Y
#define __VERTEX_SEQ_TUPLE_Y(x, y, z) ((x, y, z)) __VERTEX_SEQ_TUPLE_X
#define __VERTEX_SEQ_TUPLE_X0
#define __VERTEX_SEQ_TUPLE_Y0

#define __VERTEX_DECL_VERTEX(r, data, elem) \
    BOOST_PP_TUPLE_ELEM(3, 0, elem) BOOST_PP_TUPLE_ELEM(3, 1, elem);

#define __VERTEX_SEQ_MEMBER(x, y) x::y

#define __VERTEX_DECL_VERTEX_ATTRIBUTE(r, data, elem) \
Attribute \
{ \
  BOOST_PP_TUPLE_ELEM(3, 2, elem), \
  sizeof(__VERTEX_SEQ_MEMBER(data, BOOST_PP_TUPLE_ELEM(3, 1, elem))), \
  offsetof(data, BOOST_PP_TUPLE_ELEM(3, 1, elem)) \
},


#define VERTEX(val) \
\
struct BOOST_PP_SEQ_HEAD(val)\
{\
  BOOST_PP_SEQ_FOR_EACH(__VERTEX_DECL_VERTEX, ~, __VERTEX_SEQ_TUPLE(BOOST_PP_SEQ_TAIL(val)))\
  static const std::array<Attribute, BOOST_PP_SEQ_SIZE(__VERTEX_SEQ_TUPLE(BOOST_PP_SEQ_TAIL(val)))> mAttributeInfo;\
};\
\
const std::array<Attribute, BOOST_PP_SEQ_SIZE(__VERTEX_SEQ_TUPLE(BOOST_PP_SEQ_TAIL(val)))> \
  BOOST_PP_SEQ_HEAD(val)::mAttributeInfo = \
{ \
  BOOST_PP_SEQ_FOR_EACH(__VERTEX_DECL_VERTEX_ATTRIBUTE, BOOST_PP_SEQ_HEAD(val), __VERTEX_SEQ_TUPLE(BOOST_PP_SEQ_TAIL(val))) \
};


#endif // VertexTools_h__

