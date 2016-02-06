// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "StaticRenderAgent.h"
#include "GameObject.h"
#include "Sector.h"
#include "MeshBlockGenerator.h"
#include "..\Graphic\RegistryGraphic.h"
#include "World.h"

StaticRenderAgent::StaticRenderAgent(GameObject *parent)
  : Agent(parent, "StaticRenderAgent")
{
  
}


StaticRenderAgent::~StaticRenderAgent()
{
}