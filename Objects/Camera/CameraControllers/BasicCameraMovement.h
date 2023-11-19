#pragma once
#include <iostream>

#include "..\CameraController.h"

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class BasicCameraMovement : public CameraController
{
public:
	BasicCameraMovement(GLFWwindow* window);
	~BasicCameraMovement();

	void Controller() override;
private:
	glm::vec3 position, front, right, up, worldup = glm::vec3(0.0f, 1.0f, 0.0f);

	bool lockCamera = true;
	float deltaTime = 0.0f, lastFrame = 0.0f, yaw, pitch;
	double lastFrameMousePosX = 0.0f, lastFrameMousePosY = 0.0f;
};

