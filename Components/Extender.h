#pragma once
#include <iostream>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Extender
{
public:
	virtual void PreStart();

	virtual void Start();

	virtual void PostStart();


	virtual void PreUpdate();

	virtual void Update();

	virtual void PostUpdate();
};

