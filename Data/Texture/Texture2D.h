#pragma once
#include <iostream>

#include <glad/glad.h>

#include "..\libraries\other\stb_image.h"

class Texture2D
{
public:
	Texture2D(std::string path, bool flipImage);
	~Texture2D();

	void Set(std::string path, bool flipImage), Clear();

	std::string GetPath();
	unsigned int GetTextureID() const;
	int GetWidth() const, GetHeight() const, GetNrChannels() const, 
			GetInternalFormat() const, GetFormat() const;

private:
	unsigned int textureID;
	int width, height, nrChannels, internalFormat, format;

	std::string path;
};

