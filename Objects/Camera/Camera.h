#pragma once
#include "..\Objectoid.h"

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(GLFWwindow* window), ~Camera();
	
	float fov, nearPlane, farPlane, deltaTime, lastFrame, yaw, pitch;
	double lastFrameMousePosX, lastFrameMousePosY;
	
	glm::vec2 screenSize;
	glm::vec3 position, front, right, up, worldup;
	glm::mat4 view;

	void Update();

	glm::mat4 View(), Projection();

private:
	GLFWwindow* window;
};

