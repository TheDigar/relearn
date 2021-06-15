#pragma once

#include <glm/vec3.hpp> // glm::vec3
//#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
//#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
//#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
//#include <glm/ext/scalar_constants.hpp> // glm::pi

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class Camera_Movement {
	Forward,
	Backward,
	Left,
	Right
};

class Camera
{
private:
	glm::mat4 mView;
	glm::mat4 mProjection;
	glm::vec3 mUp;
	glm::vec3 mRight;
	glm::vec3 mFront; 
	glm::vec3 mPosition;
	glm::vec3 mWorldUp;

	float mYaw;
	float mPitch;
	float mRoll;

	const float mMovementSpeed = 2.5f;
	const float mMouseSensitivity = 0.1f;

	void UpdateVectors();

public:
	Camera(const glm::vec3& position, const float yaw, const float pitch, const float fovY, const float aspect);
	void Move(Camera_Movement direction, float deltaTime);
	void Tilt(const double& mouseDX,const double& mouseDY);
	constexpr glm::mat4& GetView() { return mView; }
	constexpr glm::mat4& GetProjection() { return mProjection; }
	constexpr glm::vec3& GetPosition() { return mPosition; }
};

