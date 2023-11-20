#pragma once
#include "..\Data\Mesh.h"
#include "..\Data\Shader\Shader.h"
#include "..\Data\Texture.h"
#include "..\Objects\Camera\Camera.h"

#include "..\Libraries\stb_image.h"

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
	Renderer
	(
		std::shared_ptr<Camera> camera,
		std::shared_ptr<Transform> transfrom,
		std::shared_ptr<Mesh> mesh, 
		std::shared_ptr<Shader> shader, 
		std::vector<std::shared_ptr<Texture>> textures
	);
	~Renderer();

	/// <summary>
	/// The name will be the variable name in the shader
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="name"></param>
	void AddTexture(std::shared_ptr<Texture> texture, std::string name);

	/// <summary>
	/// Call this to draw the renderer
	/// </summary>
	void Draw();

	std::shared_ptr<Camera> camera;
	std::shared_ptr<Transform> transfrom;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Shader> shader;

	std::vector<std::shared_ptr<Texture>> textures;
	std::vector<std::string> textureNames;
};

