#pragma once
#include <vector>
#include <memory>
#include <string>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "..\Components\Extender.h"
#include "..\Components\Transform.h"

class Object
{
public:
	Object();
	~Object();

	std::shared_ptr<Transform> transform;
	
private:

};

