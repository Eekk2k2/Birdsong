#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>

#include "..\libraries\other\stb_image.h"

class CubemapTexture
{
public:
	CubemapTexture(std::vector<std::string> paths, std::vector<bool> flip);
	~CubemapTexture();

	void Set(std::vector<std::string> paths, std::vector<bool> flip), Clear();

	std::string GetPath(int i);
	std::vector<std::string> GetPaths();

	unsigned int GetTextureID() const;

	std::vector<int> GetWidths(), GetHeights(), GetNrChannelsList(), GetInternalFormats(), GetFormats();
	int GetWidth(int i), GetHeight(int i), GetNrChannels(int i), GetInternalFormat(int i), GetFormat(int i);
private:
	unsigned textureID;
	std::vector<int> widths, heights, nrChannelsList, internalFormats, formats;
	std::vector<std::string> paths;
};

