// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderAgent_h__
#define RenderAgent_h__


#include "Agent.h"
#include <memory>
#include "..\Graphic\GameRender\IModelGenerator.h"
#include "..\Graphic\Render\Model.h"

class RenderAgent : public Agent
{
public:
  RenderAgent(GameObject *parent);
  ~RenderAgent();

  Model GetModel();

  IModelGenerator *GetModelGenerator();

private:
  std::unique_ptr<IModelGenerator> mModelGenerator;

};



#endif // RenderAgent_h__
