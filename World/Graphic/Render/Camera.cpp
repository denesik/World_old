// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Camera.h"


#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(void)
{
  mFov = 45.0f;
  mAspect = 1.0f;
  mNear = 0.1f;
  mFar = 1000.0f;
  mProjection = glm::perspective(mFov, mAspect, mNear, mFar);

  mQuat = glm::quat_cast(glm::lookAt
    (
      glm::vec3(0.0f, 0.0f, 0.0f), // eye
      glm::vec3(0.0f, 1.0f, 0.0f), // center
      glm::vec3(0.0f, 0.0f, 1.0f)  // up
      ));
}


Camera::~Camera(void)
{
}

const glm::mat4 &Camera::GetView() const
{
  return mView;
}

const glm::mat4 &Camera::GetProject() const
{
  return mProjection;
}

const glm::mat3 &Camera::GetDirection() const
{
  return mDirection;
}

void Camera::SetPos(const glm::vec3 &pos)
{
  mPos = pos;
}

void Camera::Resize(const glm::uvec2 &size)
{
  mAspect = static_cast<float>(size.x) / static_cast<float>(size.y);
  mProjection = glm::perspective(mFov, mAspect, mNear, mFar);
}

void Camera::Rotate(const glm::vec3 &degrees)
{
  mDir += degrees;
}

void Camera::Move(const glm::vec3 &dist)
{
  mPos += glm::vec3(dist.x, dist.z, -dist.y) * mQuat;
}

void Camera::Update()
{
  const auto &pitch = glm::angleAxis(mDir.x, glm::vec3(1, 0, 0));
  const auto &yaw = glm::angleAxis(mDir.z, glm::vec3(0, 0, 1));
  const auto &roll = glm::angleAxis(mDir.y, glm::vec3(0, 1, 0));
  mDir = {};

  mQuat = pitch * mQuat * yaw;
  mQuat = glm::normalize(mQuat);

  mView = glm::translate(glm::mat4_cast(mQuat), -mPos);
  mDirection = glm::mat3_cast(mQuat);
}

