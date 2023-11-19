#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

struct Position {
public:
	glm::vec3 position;

	glm::vec3 localPosition;
};

struct Rotation {
public:
	glm::vec3 rotation;

	glm::vec3 localRotation;
};

struct Scale {
public:
	Scale();

	glm::vec3 scale;

	glm::vec3 localScale;
};

class Transform
{
public:
	Transform();
	~Transform();

	Position position;
	Rotation rotation;
	Scale scale;

	Transform* parentTransform;

	glm::mat4 GetModel();
};

