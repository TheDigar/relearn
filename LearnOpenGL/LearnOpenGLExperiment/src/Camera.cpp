#include "Camera.h"


#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const float yaw, const float pitch, const float fovY, const float aspect):
	mPosition{position},
	mYaw{yaw},
	mPitch{pitch},
	mRoll{0.0f},
	mWorldUp{glm::vec3(0.0f, 1.0f, 0.0f)}
{
	UpdateVectors();

	mProjection = glm::mat4(1.0f);
	mProjection = glm::perspective(glm::radians(fovY), aspect, 0.1f, 100.0f);

	mView = glm::lookAt(mPosition, mPosition + mFront, mWorldUp);
}

void Camera::UpdateVectors()
{
	// calculate the new Front vector
	
	mFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront.y = sin(glm::radians(mPitch));
	mFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront = glm::normalize(mFront);

	// also re-calculate the Right and Up vector
	mRight = glm::normalize(glm::cross(mFront, mWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	mUp = glm::normalize(glm::cross(mRight, mFront));
}

void Camera::Move(Camera_Movement direction, float deltaTime)
{
	switch (direction)
	{
	case Camera_Movement::Forward:
		mPosition += mFront * deltaTime;
		break;
	case Camera_Movement::Backward:
		mPosition -= mFront * deltaTime;
		break;
	case Camera_Movement::Left:
		mPosition -= mRight * deltaTime;
		break;
	case Camera_Movement::Right:
		mPosition += mRight * deltaTime;
		break;
	}
	mView = glm::lookAt(mPosition, mPosition + mFront, mWorldUp);
}

void Camera::Tilt(const double& mouseDX, const double& mouseDY)
{
	mYaw += (mouseDX * mMouseSensitivity);
	mPitch += (mouseDY * mMouseSensitivity);
	if (mPitch > 89.0f)
		mPitch = 89.0f;
	else if (mPitch < -89.0f)
		mPitch = -89.0f;
	UpdateVectors();
	mView = glm::lookAt(mPosition, mPosition + mFront, mWorldUp);
}
