#pragma once
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class CameraController
{
public:
	virtual void Controller();
	
	glm::mat4 view;
	GLFWwindow* window;
};

