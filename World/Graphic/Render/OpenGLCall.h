// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef OpenGLCall_h__
#define OpenGLCall_h__

#include <GL/glew.h>
#include "../../Log.h"

static void CheckErrorsReal(const char *func, const char *file, long line)
{
  while (unsigned int openGLError = glGetError())   
  {                                                 
  LOG(error) << "GL Error." << std::endl         
  << "[" << std::endl                             
  << "  function: " << func << std::endl
  << "  error: " << openGLError << std::endl      
  << "  file: " << file << std::endl
  << "  line: " << line << std::endl
  << "]";                                         
  };
}

static void CheckErrorsFake(const char *, const char *, long)
{
}

typedef void CheckErrorsSignature(const char *, const char *, long);

#ifdef _DEBUG
static CheckErrorsSignature *CheckErrors = *CheckErrorsReal;
#else 
static CheckErrorsSignature *CheckErrors = *CheckErrorsFake;
#endif

#define GL_CALL(oglCall)                              \
  do                                                  \
  {                                                   \
    oglCall;                                          \
    CheckErrors(#oglCall, __FILE__, __LINE__);        \
  } while (0)



#endif // OpenGLCall_h__
