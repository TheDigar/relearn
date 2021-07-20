#include <SceneObject.h>

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>

SceneObject::SceneObject(Model* model, Shader* shader):
	mModel{ model },
	mShader {shader},
	mPosition {glm::vec3(0.0f)},
	mScale {glm::vec3(1.0f)},
	mYaw { 0.0f },
	mPitch {0.0f},
	mRoll { 0.0f },
	mModelMatrix{ glm::mat4(1.0f) }
{	
}

void SceneObject::BuildModelMatrix()
{
	mModelMatrix = glm::mat4(1.0f);
	mModelMatrix = glm::translate(mModelMatrix, mPosition);
	mModelMatrix = glm::scale(mModelMatrix, mScale);
	mModelMatrix *= glm::yawPitchRoll(mYaw, mPitch, mRoll);
}

void SceneObject::Draw(Camera& camera)
{
	BuildModelMatrix();

	//Transforms
	mShader->use();
	mShader->setUniformMatrix4("model", 1, GL_FALSE, glm::value_ptr(mModelMatrix));

	glm::mat3 normalMatrix = glm::inverse(camera.GetView() * mModelMatrix); 
	mShader->setUniformMatrix3("normalMatrix", 1, true, glm::value_ptr(normalMatrix));

	mModel->Draw(*mShader);
}
