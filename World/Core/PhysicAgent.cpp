// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "PhysicAgent.h"
#include "PositionAgent.h"
#include <glm/gtc/matrix_transform.hpp>


const StringIntern PhysicAgent::mPositionAgentName = StringIntern("PositionAgent");


PhysicAgent::PhysicAgent(GameObject *parent)
  : Agent(parent, "PhysicAgent")
{
  mQuat = glm::quat_cast(glm::lookAt
    (
      glm::vec3(0.0f, 0.0f, 0.0f), // eye
      glm::vec3(0.0f, 1.0f, 0.0f), // center
      glm::vec3(0.0f, 0.0f, 1.0f)  // up
      ));
}


PhysicAgent::~PhysicAgent()
{
}

void PhysicAgent::Update(const GameObjectParams &params)
{
  const auto &pitch = glm::angleAxis(mDir.x, glm::vec3(1, 0, 0));
  const auto &yaw = glm::angleAxis(mDir.z, glm::vec3(0, 0, 1));
  const auto &roll = glm::angleAxis(mDir.y, glm::vec3(0, 1, 0));
  mDir = {};

  mQuat = pitch * mQuat * yaw;
  mQuat = glm::normalize(mQuat);

  mDirection = glm::mat3_cast(mQuat);
}

void PhysicAgent::SetPos(const glm::vec3 &pos)
{
  mParent->GetFromFullName<PositionAgent>(mPositionAgentName)->Set(pos);
}

const glm::vec3 &PhysicAgent::GetPos() const
{
  return mParent->GetFromFullName<PositionAgent>(mPositionAgentName)->Get();
}

void PhysicAgent::Rotate(const glm::vec3 &degrees)
{
  mDir += degrees;
}

void PhysicAgent::Move(const glm::vec3 &dist)
{
  auto &pos = mParent->GetFromFullName<PositionAgent>(mPositionAgentName)->Get();
  pos += glm::vec3(dist.x, dist.z, -dist.y) * mQuat;
}
