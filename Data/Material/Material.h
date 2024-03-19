#pragma once
#include <vector>
#include <memory>
#include <typeindex>

#include <glad/glad.h>

#include "..\Texture.h"
#include "..\Shader\Shader.h"

typedef struct Uniform {
	std::string name;
	std::type_index type;
} Uniform;

class Material
{
public:
	Material(std::shared_ptr<Shader> shader, std::vector<std::shared_ptr<Texture>> textures),
		Material(),
		Material(Material&& other) noexcept;
		~Material();

	void Bind();

	void AddTexture(std::shared_ptr<Texture> texture, std::string uniformName);

	// TODO : RemoveTexture()

	int GetTexturesCount();

	void AddUniform(std::string uniform), AddUniform(std::string uniform, int index);

	// TODO : RemoveUniform()

	virtual void PerMaterial(), PerMesh();
	
	std::shared_ptr<Shader> shader;
private:
	
	std::vector<std::shared_ptr<Texture>> textures;
	std::vector<std::string> uniformNames;
};

