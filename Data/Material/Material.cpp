#include "Material.h"

Material::Material(std::shared_ptr<Shader> shader, std::vector<std::shared_ptr<Texture>> textures) 
{
	this->shader = shader;
	this->textures = textures;
}

Material::Material() 
{
	this->shader = std::make_shared<Shader>();
	this->textures = std::vector<std::shared_ptr<Texture>>{ };
}

Material::Material(Material&& other) noexcept 
	: textures(std::move(other.textures)), shader(std::move(other.shader)), uniformNames(std::move(other.uniformNames)) 
		{ }

Material::~Material()
{

}

void Material::Bind() 
{
	this->shader->Use();
	for (int i = 0; i < this->textures.size(); i++)
	{
		this->shader->SetInt(this->uniformNames[i], i);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i]->texture);
	}
}

void Material::AddTexture(std::shared_ptr<Texture> texture, std::string uniformName)
{
	this->textures.push_back(texture);
	this->uniformNames.push_back(uniformName);
}

int Material::GetTexturesCount()
{
	return this->textures.size();
}

void Material::AddUniform(std::string uniform)
{
	this->uniformNames.push_back(uniform);
}

void Material::AddUniform(std::string uniform, int index)
{
	this->uniformNames.insert(this->uniformNames.begin(), uniform);
}

void Material::PerMaterial()
{

}

void Material::PerMesh()
{

}


