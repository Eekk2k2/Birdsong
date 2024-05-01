#pragma once
#include <vector>
#include <memory>
#include <typeindex>

#include <glad/glad.h>

#include "..\Data\Core\Result.h"
#include "..\Data\Holder\Holder.h"

#include "..\Data\Texture\Texture2D.h"
#include "..\Data\Shader\Shader.h"

#define UNIFORM_TYPE(T) \
	constexpr typeid(T).hash_code()

// SLOW : Future optimizations
//		* Store the ID of the texture and not a pointer to it

class Material {
public:
	Material();
	Material(const Identifier& identifier, Holder& holder);
	~Material();

	BIRD_VOID Use();

	BIRD_VOID SetShader(const Identifier& identifier, Holder& holder);
	Result_Ptr<Shader> GetShader();

	Result<bool> isTextureEnrolled(const Identifier& identifier);
	BIRD_VOID EnrollTexture(std::string name, const Identifier& identifier, Holder& holder); 
	BIRD_VOID DisenrollTexture(const Identifier& identifier); 
	Result<int> TexturesEnrolled();
protected:
	Shader* shader;
	std::unordered_map<std::string, std::pair<std::string, Texture2D*>> textures;
};
