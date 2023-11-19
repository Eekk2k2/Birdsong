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


class PivotCameraController : public CameraController
{
public:
	PivotCameraController(GLFWwindow* window);
	~PivotCameraController();

	void Controller() override;
private:
	glm::vec3 position, rotation;

	float deltaTime = 0.0f, lastFrame = 0.0f;
	double lastFrameMousePosX = 0.0f, lastFrameMousePosY = 0.0f;
};

