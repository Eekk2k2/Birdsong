#pragma once

#include <Windows.h> // ::ShowWindow(::GetConsoleWindow(), SW_HIDE); and ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#include <iostream>
#include <vector>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Objects/Camera/Camera.h"
#include "Objects/Object.h"

#include "Data/Texture/CubemapTexture.h"
#include "Data/Holder/Holder.h"
#include "Data/Mesh/Mesh.h"
#include "Data/Shader/Shader.h"
#include "Data/Shader/ComputeShader.h"

class Application
{
public:
	Application();
	~Application();

	const char* APP_NAME = "Project Volume / Birdsong Engine";

	GLFWwindow* applicationWindow;

	float timeSinceMaximize, timeSinceMinimize;

	std::shared_ptr<Holder> holder;

	void Start(), Update();

	void ProcessInput();

	void Terminate(), Terminate(std::string errorMessage);
private:

};

