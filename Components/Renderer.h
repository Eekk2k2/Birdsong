#pragma once
#include "..\Data\Mesh\Mesh.h"
#include "..\Data\Shader\Shader.h"
#include "..\Data\Texture\Texture2D.h"
#include "..\Data\Material\Material.h"
#include "..\Objects\Camera\Camera.h"

#include "..\Libraries\Other\stb_image.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class Renderer
{
public:
	Renderer(
		std::shared_ptr<Camera> camera,
		std::shared_ptr<Transform> transfrom,
		std::shared_ptr<Mesh> mesh,
		std::vector<std::shared_ptr<Material>> materials
	);
	~Renderer();

	/// <summary>
	/// Call this to draw the renderer
	/// </summary>
	void Draw(Material& material) /*, Draw(unsigned int newCurrentMaterial)*/;

	void AddMaterial(), AddMaterial(std::shared_ptr<Material> material);

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Transform> transfrom;
	std::shared_ptr<Mesh> mesh;

	unsigned int currentMaterial;
	std::vector<std::shared_ptr<Material>> materials;
};

