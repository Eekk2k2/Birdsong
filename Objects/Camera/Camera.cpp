#include "Camera.h"

Camera::Camera(GLFWwindow* window)
{
	this->fov = 90.0f;
	this->nearPlane = 0.03f;
	this->farPlane = 1000.0f;

	this->deltaTime = 0.0f;
	this->lastFrame = glfwGetTime();

	this->yaw = 0.0f;
	this->pitch = 0.0f;

	this->lastFrameMousePosX = 0.0f;
	this->lastFrameMousePosY = 0.0f;

	this->screenSize = glm::vec2(1920, 1080);

	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, 0.0f);
	this->right = glm::vec3(0.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0.0f, 0.0f, 0.0f);
	this->worldup = glm::vec3(0.0f, 1.0f, 0.0f);

	this->view = glm::mat4(1.0f);

	this->window = window;
	//this->cameraController = new BasicCameraMovement(this->window);
	//this->cameraController->Controller();
}

Camera::~Camera() {  }

void Camera::Update()
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

	// Look
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		glfwSetCursorPos(this->window, 1920.0f / 2.0f, 1080.0f / 2);

		this->yaw += (float)deltaMousePosX * 0.1f;
		this->pitch += (float)deltaMousePosY * 0.1f;
		if (this->pitch > 89.0f) pitch = 89.0f;
		if (this->pitch < -89.0f) pitch = -89.0f;
	}

	glfwGetCursorPos(this->window, &this->lastFrameMousePosX, &this->lastFrameMousePosY);

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

glm::mat4 Camera::View() 
{
	return this->view;
}

glm::mat4 Camera::Projection() {
	return glm::perspective(glm::radians(fov), (float)screenSize.x / (float)screenSize.y, this->nearPlane, this->farPlane);
}