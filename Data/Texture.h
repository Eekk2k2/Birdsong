#pragma once
#include <iostream>

#include <glad/glad.h>

#include "..\Libraries\stb_image.h"

class Texture
{
public:
	Texture(int WRAPPING, const char* filename, bool flipImage);
	~Texture();

	unsigned int texture;

	int width, height, nrChannels;
};

