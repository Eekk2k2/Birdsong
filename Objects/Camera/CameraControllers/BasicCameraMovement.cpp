#include "BasicCameraMovement.h"

BasicCameraMovement::BasicCameraMovement(GLFWwindow* window)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, 0.0f);
	this->right = glm::vec3(0.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0.0f, 0.0f, 0.0f);
	this->worldup = glm::vec3(0.0f, 1.0f, 0.0f);

	this->yaw = 0.0f;
	this->pitch = 0.0f;

	this->window = window;
}

BasicCameraMovement::~BasicCameraMovement()
{
}

void BasicCameraMovement::Controller()
{
	// Delta time calculation
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// Delta mouse calculation and mouse locking
	double currentFrameMousePosX = 0.0f, currentFrameMousePosY = 0.0f, deltaMousePosX, deltaMousePosY;
	glfwGetCursorPos(this->window, &currentFrameMousePosX, &currentFrameMousePosY);
	deltaMousePosX = currentFrameMousePosX - this->lastFrameMousePosX;
	deltaMousePosY = this->lastFrameMousePosY - currentFrameMousePosY;
	glfwSetCursorPos(this->window, 1920.0f / 2.0f, 1080.0f / 2);
	glfwGetCursorPos(this->window, &this->lastFrameMousePosX, &this->lastFrameMousePosY);

	// Look
	this->yaw += (float)deltaMousePosX * 0.1f;
	this->pitch += (float)deltaMousePosY * 0.1f;
	if (this->pitch > 89.0f) pitch = 89.0f;
	if (this->pitch < -89.0f) pitch = -89.0f;
	
	//std::cout << deltaMousePosX << " " << deltaMousePosY << std::endl;
	//std::cout << this->yaw << " " << this->pitch << std::endl;
	//std::cout << "\n \n";

	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);

	this->right = glm::normalize(glm::cross(front, worldup));
	this->up = glm::normalize(glm::cross(right, front));

	// Movement
	float horizontal = 0, vertical = 0, elevation = 0, speed = 10;
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)			vertical -= 1;
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)			vertical += 1;
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)			horizontal -= 1;
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)			horizontal += 1;
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)		elevation += 1;
	if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)	elevation -= 1;

	this->position += ((this->right * horizontal) + (this->front * vertical * -1.0f) + (this->up * elevation)) * speed * deltaTime;

	// Reset
	if (glfwGetKey(this->window, GLFW_KEY_HOME) == GLFW_PRESS) {
		this->position = glm::vec3(0, 0, -10.20);
		this->yaw = 0.0f;
		this->pitch = 0.0f;
	};

	this->view = glm::lookAt(this->position, this->position + this->front, this->up);
}
