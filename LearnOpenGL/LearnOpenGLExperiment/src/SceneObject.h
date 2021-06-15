#pragma once
#include <Shader.h>
#include <Model.h>
#include <Camera.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class SceneObject
{
private:
	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::mat4 mModelMatrix;
	float mYaw;
	float mPitch;
	float mRoll;
    Model* mModel;
    Shader* mShader;

	void BuildModelMatrix();

public:
    SceneObject(Model* model, Shader* shader);
    void Draw(Camera& camera);
	constexpr void SetPosition(const glm::vec3& pos) { mPosition = pos; }
	constexpr void SetScale(const glm::vec3& scale) { mScale = scale; }
	constexpr void SetYaw(const float& yaw) { mYaw = yaw; }
	constexpr void SetPitch(const float& pitch) { mPitch = pitch; }
	constexpr void SetRoll(const float& roll) { mRoll = roll; }

	constexpr const glm::vec3& GetPosition() { return mPosition; }
	constexpr const glm::vec3& GetScale() { return mScale; }
	constexpr const float& GetYaw() { return mYaw; }
	constexpr const float& GetPitch() { return mPitch; }
	constexpr const float& GetRoll() { return mRoll; }
};

