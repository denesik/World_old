// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef MultiModel_h__
#define MultiModel_h__

#include "Model.h"


class MultiModel
{
public:
  MultiModel();
  ~MultiModel();

  void Push(const Model &model);

  const PMesh &GetMesh() const noexcept;

  PMesh &GetMesh() noexcept;

  const PTexture &GetTexture() const noexcept;

private:
  PMesh mMesh;
  PTexture mTexture;

};



#endif // MultiModel_h__