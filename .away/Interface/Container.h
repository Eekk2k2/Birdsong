#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "Elements/Element.h"

class Container
{
public:
	std::vector<Element> elements;
private:
	GLuint VAO, VBO;
};

