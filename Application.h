#pragma once

#include <Windows.h> // ::ShowWindow(::GetConsoleWindow(), SW_HIDE); and ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
#include <iostream>
#include <vector>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Holder.h"

#include "Objects/Camera/Camera.h"
#include "Objects/MainObject.h"

#include "Data/Mesh.h"
#include "Data/Shader/Shader.h"

#include "Components/Renderer.h"

#include "Data/Shader/ComputeShader.h"


class Application
{
public:
	Application();
	~Application();

	const char* APP_NAME = "Project Volume / Birdsong Engine";

	GLFWwindow* applicationWindow;

	float timeSinceMaximize;
	float timeSinceMinimize;

	void Start();

	void Update();

	void ProcessInput();

	void Terminate();

	void Terminate(std::string errorMessage);
private:
	std::unique_ptr<Holder> holder;
};

