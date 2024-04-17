#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
}

BS_VOID Material::Bind()
{
	if (this->shader == nullptr)
		return BS_VOID(false, "Shader of Material is nullptr. To set the shader of a material use Material::SetShader()");

	this->shader->Use();
	int i = 0;
	for (auto& texture : this->textures)
	{
		this->shader->SetInt(texture.second.first, texture.second.second->GetTextureID());
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texture.second.second->GetTextureID());
		
		i++;
	}

	return BS_VOID(nullptr);
}

BS_VOID Material::SetShader(const Identifier& identifier, const Holder& holder)
{
	Result_Ptr<Shader> shaderResult = holder.GetHeldItem<Shader>(identifier);
	if (!shaderResult.success)
		return BS_VOID(false, shaderResult.info);

	this->shader = shaderResult.item;
	return BS_VOID(nullptr);
}

Result_Ptr<Shader> Material::GetShader()
{
	return Result_Ptr<Shader>(this->shader);
}

Result<bool> Material::isTextureEnrolled(const Identifier& identifier)
{
	if (identifier.typeID != typeid(Texture2D))
		return Result<bool>(false, "typeID of identifier in Material::TexturesEnrolled need to match typeid(Texture2D)");

	if (this->textures.find(identifier.UUID) != this->textures.end())
		return Result<bool>(true);
	else
		return Result<bool>(false);
}

BS_VOID Material::EnrollTexture(std::string name, const Identifier& identifier, const Holder& holder)
{
	// Texture isnt enrolled
	Result<bool> textureEnrolled = this->isTextureEnrolled(identifier);
	if (!textureEnrolled.success)
		return BS_VOID(false, textureEnrolled.info);

	if (textureEnrolled.item)
		return BS_VOID(false, "texture2d of identifier in EnrollTexture(name, identifier, holder) is already enrolled");

	// Texture exists
	Result_Ptr<Texture2D> textureResult = holder.GetHeldItem<Texture2D>(identifier);
	if (!textureResult.success)
		return BS_VOID(false, textureResult.info);

	// Add
	this->textures.emplace(identifier.UUID, std::pair<std::string, Texture2D*>(name, textureResult.item));
	return BS_VOID(nullptr);
}

BS_VOID Material::DisenrollTexture(const Identifier& identifier)
{
	// Texture does exist
	Result<bool> textureEnrolled = this->isTextureEnrolled(identifier);
	if (!textureEnrolled.success)
		return BS_VOID(false, textureEnrolled.info);

	if (!textureEnrolled.item)
		return BS_VOID(false, "texture2d of identifier in DisenrollMaterial(identifier) is not enrolled");

	// Erase
	this->textures.erase(identifier.UUID);
	return BS_VOID(nullptr);
}

Result<int> Material::TexturesEnrolled()
{
	return Result<int>(this->textures.size());
}

//Material::Material(std::shared_ptr<Shader> shader, std::vector<std::shared_ptr<Texture2D>> textures) 
//{
//	this->shader = shader;
//	this->textures = textures;
//}
//
//Material::Material() 
//{
//	this->shader = std::make_shared<Shader>();
//	this->textures = std::vector<std::shared_ptr<Texture2D>>{ };
//}
//
//Material::Material(Material&& other) noexcept 
//	: textures(std::move(other.textures)), shader(std::move(other.shader)), uniformNames(std::move(other.uniformNames)) 
//		{ }
//
//Material::Material(const Material& other) : textures(other.textures), shader(other.shader), uniformNames(other.uniformNames) { }
//


//void Material::AddTexture(std::shared_ptr<Texture2D> textureID, std::string uniformName)
//{
//	this->textures.push_back(textureID);
//	this->uniformNames.push_back(uniformName);
//}
//
//int Material::GetTexturesCount()
//{
//	return this->textures.size();
//}
//
//void Material::AddUniform(std::string uniform)
//{
//	this->uniformNames.push_back(uniform);
//}
//
//void Material::AddUniform(std::string uniform, int index)
//{
//	this->uniformNames.insert(this->uniformNames.begin(), uniform);
//}
//
//void Material::PerMaterial()
//{
//
//}
//
//void Material::PerMesh()
//{

//}

