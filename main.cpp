#include "main.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Libraries\Other\stb_image.h"

int main() {
	
#ifdef ENABLE_FILE_HANDLER

	//std::string assetConfiguration = ".\\Assets\\Shaders\\Minimum\\minimum.birds";
	//std::string compiledAsset = ".\\Assets\\Shaders\\Minimum\\minimum.cbirds";
	//BIRD_VOID compilationResult = Loader::CompileShaderAsset(assetConfiguration);
	//if (!compilationResult.success) { compilationResult.Print(); }

	//Result<Loader::ShaderAsset> loadResult = Loader::LoadShaderAsset(compiledAsset);
	//if (!compilationResult.success) { compilationResult.Print(); }

	//std::string assetConfiguration = ".\\Assets\\Materials\\MinimumMat\\minimum.birdm";
	//std::string compiledAsset = ".\\Assets\\Materials\\MinimumMat\\minimum.cbirdm";
	//BIRD_VOID compilationResult = Loader::CompileMaterialAsset(assetConfiguration);
	//if (!compilationResult.success) { compilationResult.Print(); }

	//Loader::LoadMaterialAsset(compiledAsset);

	//Loader::quickSave();
	//Loader::quickLoad();

	//Loader::CompileShaderConfig(".\\Assets\\Shaders\\Minimum\\minimum.birds");
	//
	//if (!asd.success) { asd.Print(); }

	//Result<Identifier> asd = Result<Identifier>(false, "");
	//BIRD_VOID asd = BIRD_VOID(nullptr);
	//auto start = std::chrono::high_resolution_clock::now();
	//for (size_t i = 0; i < 10000; i++)
	//{
	//	asd = Loader::CompileShaderConfig(".\\Assets\\Shaders\\Minimum\\minimum.birds");
	//}
	//auto finish = std::chrono::high_resolution_clock::now();

	//auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	//std::cout << microseconds.count() << "\n";

#endif // ENABLE_FILE_HANDLER


#ifdef ENABLE_MATERIAL_BUILDER
	std::cout << (typeid(bool).hash_code() == BIRD_UNIFORM_BOOL) << std::endl;
	std::cout << (typeid(int).hash_code() == BIRD_UNIFORM_INT) << std::endl;
	std::cout << (typeid(unsigned int).hash_code() == BIRD_UNIFORM_UINT) << std::endl;
	std::cout << (typeid(float).hash_code() == BIRD_UNIFORM_FLOAT) << std::endl;
	std::cout << (typeid(glm::vec2).hash_code() == BIRD_UNIFORM_VEC2) << std::endl;
	std::cout << (typeid(glm::vec3).hash_code() == BIRD_UNIFORM_VEC3) << std::endl;
	std::cout << (typeid(glm::vec4).hash_code() == BIRD_UNIFORM_VEC4) << std::endl;
	std::cout << (typeid(glm::mat2).hash_code() == BIRD_UNIFORM_MAT2) << std::endl;
	std::cout << (typeid(glm::mat3).hash_code() == BIRD_UNIFORM_MAT3) << std::endl;
	std::cout << (typeid(glm::mat4).hash_code() == BIRD_UNIFORM_MAT4) << std::endl;
	std::cout << (typeid(glm::mat2x3).hash_code() == BIRD_UNIFORM_MAT2x3) << std::endl;
	std::cout << (typeid(glm::mat3x2).hash_code() == BIRD_UNIFORM_MAT3x2) << std::endl;
	std::cout << (typeid(glm::mat2x4).hash_code() == BIRD_UNIFORM_MAT2x4) << std::endl;
	std::cout << (typeid(glm::mat4x2).hash_code() == BIRD_UNIFORM_MAT4x2) << std::endl;
	std::cout << (typeid(glm::mat3x4).hash_code() == BIRD_UNIFORM_MAT3x4) << std::endl;
	std::cout << (typeid(glm::mat4x3).hash_code() == BIRD_UNIFORM_MAT4x3) << std::endl;
#endif // ENABLE_MATERIAL_BUILDER 

#ifdef ENABLE_APPLICATION
	std::cout << "The Application of Birdsong is enabled" << std::endl;
	application = new Application();

	application->Start();

	while (!glfwWindowShouldClose(application->applicationWindow))
		application->Update();

	application->Terminate();
#endif // ENABLE_APPLICATION 

	return 0;
}