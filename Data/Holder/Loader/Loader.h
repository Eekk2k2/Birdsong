#pragma once
#include <fstream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "..\Data\Core\Result.h"
#include "..\Data\Core\Identifier.h"
#include "..\Data\Holder\Holder.h"
#include "..\Data\Shader\Shader.h"

typedef enum : unsigned long long {
	BIRD_UNIFORM_BOOL = 0x9531807BCB34007,
	BIRD_UNIFORM_INT = 0xAF64054C2966377B,
	BIRD_UNIFORM_UINT = 0xAF64044C296634C8,
	BIRD_UNIFORM_FLOAT = 0xAF64004C296629F4,
	BIRD_UNIFORM_VEC2 = 0x1613DD2B3DBF243B,
	BIRD_UNIFORM_VEC3 = 0x85BE2EA1D8F0D256,
	BIRD_UNIFORM_VEC4 = 0xC6CBE525AAE286BB,
	BIRD_UNIFORM_MAT2 = 0xEFA565A326EE138E,
	BIRD_UNIFORM_MAT3 = 0x5B2B39DFEBA61CA4,
	BIRD_UNIFORM_MAT4 = 0xB474736AB35C0FFB,
	BIRD_UNIFORM_MAT2x3 = 0x1EF8FCBF36B517BD,
	BIRD_UNIFORM_MAT3x2 = 0xAFD08ED175F986F5,
	BIRD_UNIFORM_MAT2x4 = 0xEABF0EF89688E783,
	BIRD_UNIFORM_MAT4x2 = 0x8A49A7FF7F3E61A0,
	BIRD_UNIFORM_MAT3x4 = 0x8F6527A6D3C600A4,
	BIRD_UNIFORM_MAT4x3 = 0x2623E4BECB310026
} UNIFORM_TYPE;


namespace Serializer {
	// Retrieves the has code for a given type
	#define SERIALIZER_KEY(T) (unsigned __int64)typeid(T).hash_code()
	
	static void SerializeString(void* data_in, std::ofstream& ostrm) {
		std::string* str = (std::string*)data_in;
		unsigned __int64 length = str->size();
		ostrm.write(reinterpret_cast<const char*>(&length), sizeof(length));
		ostrm.write(reinterpret_cast<const char*>(str->data()), length);
	}

	static void SerializeBool(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(bool));
	}
	
	static void SerializeInt(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(int));
	}

	static void SerializeUnsignedInt(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(unsigned int));
	}

	static void SerializeFloat(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(float));
	}

	static void SerializeVec2(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::vec2));
	}

	static void SerializeVec3(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::vec3));
	}

	static void SerializeVec4(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::vec4));
	}

	static void SerializeMat2(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat2));
	}

	static void SerializeMat3(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat3));
	}

	static void SerializeMat4(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat4));
	}

	static void SerializeMat2x3(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat2x3));
	}

	static void SerializeMat3x2(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat3x2));
	}

	static void SerializeMat2x4(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat2x4));
	}

	static void SerializeMat4x2(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat4x2));
	}

	static void SerializeMat3x4(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat3x4));
	}

	static void SerializeMat4x3(void* data_in, std::ofstream& ostrm) {
		ostrm.write(reinterpret_cast<const char*>(data_in), sizeof(glm::mat4x3));
	}

	// This maps a certain type to its serialize function
	static std::unordered_map<unsigned __int64, void(*)(void*, std::ofstream&)> typeSerializers
	{
		{ SERIALIZER_KEY(std::string),	&SerializeString		},
		{ SERIALIZER_KEY(bool),			&SerializeBool			},
		{ SERIALIZER_KEY(int),			&SerializeInt			},
		{ SERIALIZER_KEY(unsigned int), &SerializeUnsignedInt	},
		{ SERIALIZER_KEY(float),		&SerializeFloat			},
		{ SERIALIZER_KEY(glm::vec2),	&SerializeVec2			},
		{ SERIALIZER_KEY(glm::vec3),	&SerializeVec3			},
		{ SERIALIZER_KEY(glm::vec4),	&SerializeVec4			},
		{ SERIALIZER_KEY(glm::mat2),	&SerializeMat2			},
		{ SERIALIZER_KEY(glm::mat3),	&SerializeMat3			},
		{ SERIALIZER_KEY(glm::mat4),	&SerializeMat4			},
		{ SERIALIZER_KEY(glm::mat2x3),	&SerializeMat2x3		},
		{ SERIALIZER_KEY(glm::mat3x2),	&SerializeMat3x2		},
		{ SERIALIZER_KEY(glm::mat2x4),	&SerializeMat2x4		},
		{ SERIALIZER_KEY(glm::mat4x2),	&SerializeMat4x2		},
		{ SERIALIZER_KEY(glm::mat3x4),	&SerializeMat3x4		},
		{ SERIALIZER_KEY(glm::mat4x3),	&SerializeMat4x3		}
	};

	static void DeserializeString(void* data_out, std::ifstream& istrm) {
		unsigned __int64 length;
		istrm.read(reinterpret_cast<char*>(&length), sizeof(length));

		std::string* str = (std::string*)data_out;
		str->resize(length);
		istrm.read(reinterpret_cast<char*>(str->data()), length);
	}

	static void DeserializeBool(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(bool));
	}

	static void DeserializeInt(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(int));
	}

	static void DeserializeUnsignedInt(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(unsigned int));
	}

	static void DeserializeFloat(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(float));
	}

	static void DeserializeVec2(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::vec2));
	}

	static void DeserializeVec3(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::vec3));
	}

	static void DeserializeVec4(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::vec4));
	}

	static void DeserializeMat2(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat2));
	}

	static void DeserializeMat3(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat3));
	}

	static void DeserializeMat4(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat4));
	}

	static void DeserializeMat2x3(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat2x3));
	}

	static void DeserializeMat3x2(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat3x2));
	}

	static void DeserializeMat2x4(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat2x4));
	}

	static void DeserializeMat4x2(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat4x2));
	}

	static void DeserializeMat3x4(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat3x4));
	}

	static void DeserializeMat4x3(void* data_out, std::ifstream& istrm) {
		istrm.read(reinterpret_cast<char*>(data_out), sizeof(glm::mat4x3));
	}

	// This maps a certain type to its deserialize function
	static std::unordered_map<unsigned __int64, void(*)(void*, std::ifstream&)> typeDeserializers
	{
		{ SERIALIZER_KEY(std::string),	&DeserializeString		},
		{ SERIALIZER_KEY(bool),			&DeserializeBool		},
		{ SERIALIZER_KEY(int),			&DeserializeInt			},
		{ SERIALIZER_KEY(unsigned int), &DeserializeUnsignedInt },
		{ SERIALIZER_KEY(float),		&DeserializeFloat		},
		{ SERIALIZER_KEY(glm::vec2),	&DeserializeVec2		},
		{ SERIALIZER_KEY(glm::vec3),	&DeserializeVec3		},
		{ SERIALIZER_KEY(glm::vec4),	&DeserializeVec4		},
		{ SERIALIZER_KEY(glm::mat2),	&DeserializeMat2		},
		{ SERIALIZER_KEY(glm::mat3),	&DeserializeMat3		},
		{ SERIALIZER_KEY(glm::mat4),	&DeserializeMat4		},
		{ SERIALIZER_KEY(glm::mat2x3),	&DeserializeMat2x3		},
		{ SERIALIZER_KEY(glm::mat3x2),	&DeserializeMat3x2		},
		{ SERIALIZER_KEY(glm::mat2x4),	&DeserializeMat2x4		},
		{ SERIALIZER_KEY(glm::mat4x2),	&DeserializeMat4x2		},
		{ SERIALIZER_KEY(glm::mat3x4),	&DeserializeMat3x4		},
		{ SERIALIZER_KEY(glm::mat4x3),	&DeserializeMat4x3		},
	};



	static void Serialize(unsigned __int64 typeHash, void* in, std::ofstream& ostrm) {
		typeSerializers[typeHash](in, ostrm);
	}

	static void Deserialize(unsigned __int64 typeHash, void* out, std::ifstream& istrm) {
		typeDeserializers[typeHash](out, istrm);
	}

	template <typename T>
	static void Serialize(void* in, std::ofstream& ostrm) {
		unsigned __int64 typeHash = typeid(T).hash_code();
		typeSerializers[typeHash](in, ostrm);
	}

	template <typename T>
	static void Deserialize(void* out, std::ifstream& istrm) {
		unsigned __int64 typeHash = typeid(T).hash_code();
		typeDeserializers[typeHash](out, istrm);
	}
}


namespace Loader {

	static inline Result<std::string> LoadText(std::string path) {
		std::ifstream pathFile(path);
		if (!pathFile.good()) 
			return Result<std::string>(false, "Failed to load path " + path + " when retrieving text file contents.");

		std::stringstream contentStream;
		contentStream << pathFile.rdbuf();
		pathFile.close();
		return contentStream.str();
	}

	static inline Result<json> LoadJson(std::string path) {
		Result<std::string> contents = Loader::LoadText(path);
		if (!contents.success) { return Result<json>(false, contents.info); }

		return Result<json>(json::parse(contents.item));
	}

	static inline bool isPathValid(std::string path, std::string prefix, std::string suffix) {
		if (path.empty()) return false;
		if (!path.rfind(prefix, 0) == 0) return false; // Check prefix 
		if (path.substr(path.size() - suffix.size()) != suffix) return false; // Check suffix

		return true;
	}

	// Creates the asset file (.cbird) from a asset config file (.bird)
	static BIRD_VOID CompileShaderConfig(std::string path) {
		std::string suffix = ".birds";
		if (!isPathValid(path, ".\\Assets", suffix)) return BIRD_VOID(false, "Loader::CompieShaderConfig(" + path + ") failed because the path is not valid");

		// Load config
		Result<json> config = Loader::LoadJson(path);
		if (!config.success) return BIRD_VOID(false, config.info);

		// Serialize/Compile data
		std::string assetFile(path);
		assetFile.insert(assetFile.size() - suffix.size() + 1, 1, 'c');
		std::ofstream strm(assetFile, std::ios::binary);

		std::string identifier = "identifier not supported yet";

		std::string vertexShaderCode = "";
		std::string vertexShaderPath = config.item["vert"].get<std::string>();
		if (isPathValid(vertexShaderPath, ".\\Assets", ".vert")) vertexShaderCode = Loader::LoadText(vertexShaderPath);

		std::string fragmentShaderCode = "";
		std::string fragmentShaderPath = config.item["frag"].get<std::string>();
		if (isPathValid(fragmentShaderPath, ".\\Assets", ".vert")) fragmentShaderCode = Loader::LoadText(fragmentShaderPath);

		std::string geometryShaderCode = "";
		std::string geometryShaderPath = config.item["geom"].get<std::string>();
		if (isPathValid(fragmentShaderPath, ".\\Assets", ".geom")) geometryShaderCode = Loader::LoadText(geometryShaderPath);

		Serializer::Serialize<std::string>(&identifier, strm);
		Serializer::Serialize<std::string>(&vertexShaderCode, strm);
		Serializer::Serialize<std::string>(&fragmentShaderCode, strm);
		Serializer::Serialize<std::string>(&geometryShaderCode, strm);

		return BIRD_VOID(nullptr);
	}

	static Result<Identifier> LoadShader(std::string path, Holder* holder) {
		if (!isPathValid(path, ".\\Assets", ".cbirds")) return Result<Identifier>(false, "Loader::LoadShader('" + path + "', holder) failed because the path is not valid");
		
		// Load
		std::ifstream strm(path, std::ios::binary);

		std::string identifier;
		std::string vertexShaderCode;
		std::string fragmentShaderCode;
		std::string geometryShaderCode;

		Serializer::Deserialize<std::string>(&identifier, strm);
		Serializer::Deserialize<std::string>(&vertexShaderCode, strm);
		Serializer::Deserialize<std::string>(&fragmentShaderCode, strm);
		Serializer::Deserialize<std::string>(&geometryShaderCode, strm);

		// Create
		Result<Identifier> shaderIdentifier = holder->AddNewItem<Shader>();
		if (!shaderIdentifier.success) { return shaderIdentifier; }
		Result_Ptr<Shader> shader = holder->GetHeldItem<Shader>(shaderIdentifier.item);
		if (!shader.success) { return Result<Identifier>(false, shader.info); }

		if (!vertexShaderCode.empty()) shader.item->SetVert(SHADER_FROMCODE, vertexShaderCode.c_str());
		if (!fragmentShaderCode.empty()) shader.item->SetVert(SHADER_FROMCODE, fragmentShaderCode.c_str());
		if (!geometryShaderCode.empty()) shader.item->SetVert(SHADER_FROMCODE, geometryShaderCode.c_str());

		shader.item->LinkProgram();
		return shaderIdentifier; 
	}
}
