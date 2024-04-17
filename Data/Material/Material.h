#pragma once
#include <vector>
#include <memory>
#include <typeindex>

#include <glad/glad.h>

#include "..\Data\Core\Result.h"
#include "..\Data\Holder\Holder.h"

#include "..\Data\Texture\Texture2D.h"
#include "..\Data\Shader\Shader.h"

// Future optimizations :
//		* Store the ID of the texture and not a pointer to it

class Material {
public:
	Material();
	~Material();

	BS_VOID Bind();

	BS_VOID SetShader(const Identifier& identifier, const Holder& holder);
	Result_Ptr<Shader> GetShader();

	Result<bool> isTextureEnrolled(const Identifier& identifier);
	BS_VOID EnrollTexture(std::string name, const Identifier& identifier, const Holder& holder); 
	BS_VOID DisenrollTexture(const Identifier& identifier); 
	Result<int> TexturesEnrolled();

protected:
	Shader* shader;
	std::unordered_map<std::string, std::pair<std::string, Texture2D*>> textures;
};

//typedef struct Uniform {
//	std::string name;
//	std::type_index type;
//} Uniform;
//
//class Material
//{
//public:
//	Material(std::shared_ptr<Shader> shader, std::vector<std::shared_ptr<Texture2D>> textures),
//		Material(),
//		Material(Material&& other) noexcept,
//		Material(const Material& other);
//		~Material();
//
//	void Bind();
//
//	void AddTexture(std::shared_ptr<Texture2D> textureID, std::string uniformName);
//
//	// TODO : RemoveTexture()
//
//	int GetTexturesCount();
//
//	void AddUniform(std::string uniform), AddUniform(std::string uniform, int index);
//
//	// TODO : RemoveUniform()
//
//	virtual void PerMaterial(), PerMesh();
//	
//	std::shared_ptr<Shader> shader;
//private:
//	
//	std::vector<std::shared_ptr<Texture2D>> textures;
//	std::vector<std::string> uniformNames;
//};

