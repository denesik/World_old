// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Block_h__
#define Block_h__

#include "GameObject.h"
#include "RenderAgent.h"

typedef std::shared_ptr<class Block> PBlock;

/// Ѕлок. ћожет быть статическим или динамическим.
/// ” статического блока есть статический рендер агент.
/// ” динамического блока есть статический либо динамический рендер агент.
/// ќбновление статического рендер агента инициируетс€ сектором 
/// каждый раз при изменении статической геометрии сектора.
/// ќбновление динамического рендер агента инициируетс€ блоком каждый фрейм.
class Block : public GameObject
{
public:
  Block();
  ~Block();

  PGameObject Clone() override;

  void Update(GameObjectParams &params) override;

  void UpdateGraphic(GameObjectParams &params);

  inline bool IsStatic() const noexcept
  {
    return mIsStatic;
  }

private:
  friend class DB;
  static const StringIntern mRenderAgentName;
  const bool mIsStatic = true;
};



#endif // Block_h__