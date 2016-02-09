// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Player.h"
#include "PhysicAgent.h"

const StringIntern Player::mPhysicAgentName = StringIntern("PhysicAgent");


Player::Player()
{
}


Player::~Player()
{
}

PGameObject Player::Clone()
{
  return MakeGameObject<Player>();
}

void Player::Rotate(const glm::vec3 &degrees)
{
  GetFromFullName<PhysicAgent>(mPhysicAgentName)->Rotate(degrees);
}

void Player::Move(const glm::vec3 &dist)
{
  GetFromFullName<PhysicAgent>(mPhysicAgentName)->Move(dist);
}

const glm::vec3 & Player::GetPosition() const
{
  return GetFromFullName<PhysicAgent>(mPhysicAgentName)->GetPos();
}

void Player::SetPosition(const glm::vec3 &pos)
{
  GetFromFullName<PhysicAgent>(mPhysicAgentName)->SetPos(pos);
}
