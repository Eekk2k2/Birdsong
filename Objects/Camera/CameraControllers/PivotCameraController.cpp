#include "PivotCameraController.h"

// NOT FINISHED AS I NEVER FIGURED OUT THE MATH




PivotCameraController::PivotCameraController(GLFWwindow* window)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->window = window;
}

PivotCameraController::~PivotCameraController()
{
}

void PivotCameraController::Controller()
{
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	double currentFrameMousePosX = 0.0f, currentFrameMousePosY = 0.0f, deltaMousePosX, deltaMousePosY;
	glfwGetCursorPos(this->window, &currentFrameMousePosX, &currentFrameMousePosY);
	deltaMousePosX = currentFrameMousePosX - this->lastFrameMousePosX;
	deltaMousePosY = currentFrameMousePosY - this->lastFrameMousePosY;
	glfwSetCursorPos(this->window, 1920.0f / 2.0f, 1080.0f / 2);
	glfwGetCursorPos(this->window, &this->lastFrameMousePosX, &this->lastFrameMousePosY);

	int sensitivity = 1;
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS && glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		this->position += glm::vec3(deltaMousePosX * 1.5f, -deltaMousePosY * 1.5f, 0.0f) * deltaTime;

	int horizontal = 0, vertical = 0, elevation = 0, speed = 10;
	if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)			horizontal	-= 1;
	if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)			horizontal	+= 1;
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)			vertical	-= 1;
	if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)			vertical	+= 1;
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)		elevation	+= 1;
	if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)	elevation	-= 1;

	this->position += glm::vec3(speed, speed, speed) * (glm::vec3(vertical, elevation, horizontal) * -1.0f) * deltaTime;

	this->view = glm::translate(glm::mat4(1.0f), this->position);

	if (glfwGetKey(this->window, GLFW_KEY_HOME) == GLFW_PRESS) position = glm::vec3(0, 0, -10.20);
}




















////Rotate around pivot matrix (T2(x, x, x) * R * T1(-x, -x, -x))
////Since the camera doesnt rotate for some reason we have to 
////calculate just the postion from this. The rotation is applied 
////afterwards again, through a separate process.
//glm::mat4 translation1 = glm::translate(glm::mat4(1.0f), -this->pivot);
//glm::mat4 rotation1 = glm::mat4(1.0f);
//rotation1 = glm::rotate(rotation1, glm::radians(0.0f), glm::vec3(1, 0, 0));	// X
//rotation1 = glm::rotate(rotation1, glm::radians(0.0f), glm::vec3(0, 1, 0));	// Y
//glm::mat4 translation2 = glm::translate(glm::mat4(1.0f), this->pivot);
//glm::mat4 pivotRotation = translation2 * rotation1 * translation2;
//glm::vec3 positionFromRotation = glm::vec3(pivotRotation[3]);

//this->view = glm::translate(glm::mat4(1.0f), positionFromRotation + glm::vec3(0, 0, -this->pivotDistance));

////glm::mat4 rotation2 = glm::mat4(1.0f);
////rotation2 = glm::rotate(rotation2, glm::radians(-rotx), glm::vec3(1, 0, 0));	// X
////rotation2 = glm::rotate(rotation2, glm::radians(-roty), glm::vec3(0, 1, 0));	// Y

////this->view = glm::lookAt(glm::vec3(pivotRotation * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -this->pivotDistance))[3]), pivot, glm::vec3(0, 1, 0));

////// Update zoomDistance
////// Update pivot pos or rotation
////
////// Translate back scroll amount
////this->view = glm::translate(view, glm::vec3(0, 0, -this->pivotDistance));

////// Rotate 

////// Trasnalte to pivot pos
////this->view = glm::translate(view, glm::vec3(this->pivot));
