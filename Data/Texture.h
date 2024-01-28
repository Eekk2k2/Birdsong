#pragma once
#include <iostream>

#include <glad/glad.h>

#include "..\libraries\other\stb_image.h"

class Texture
{
public:
	Texture(int WRAPPING, const char* filename, bool flipImage, std::string name);
	~Texture();

	unsigned int texture;

	int width, height, nrChannels;

	std::string name;
};

