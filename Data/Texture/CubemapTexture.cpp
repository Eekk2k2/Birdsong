#include "CubemapTexture.h"

CubemapTexture::CubemapTexture(std::vector<std::string> paths, std::vector<bool> flip)
{
	this->Set(paths, flip);
}

CubemapTexture::~CubemapTexture()
{
	this->Clear();
}

void CubemapTexture::Set(std::vector<std::string> paths, std::vector<bool> flip)
{
	this->Clear();

	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

	for (size_t i = 0; i < paths.size(); i++)
	{
		stbi_set_flip_vertically_on_load(flip[i]);
		unsigned char* imageData = stbi_load(paths[i].c_str(), &this->widths[i], &this->heights[i], &this->nrChannelsList[i], 0);
		if (imageData) {
			// Determine texture type
			switch (this->nrChannelsList[i]) {
			case 1:
				this->internalFormats[i] = GL_RED;
				this->formats[i] = GL_RED;
				break;
			case 2:
				this->internalFormats[i] = GL_RED;
				this->formats[i] = GL_RED;
				break;
			case 3:
				this->internalFormats[i] = GL_SRGB;
				this->formats[i] = GL_RGB;
				break;
			case 4:
				this->internalFormats[i] = GL_SRGB_ALPHA;
				this->formats[i] = GL_RGBA;
				break;
			default:
				this->internalFormats[i] = GL_RED;
				this->formats[i] = GL_RED;
				break;
			}

			// Set the texture
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, this->internalFormats[i], this->widths[i], this->heights[i], 0, this->formats[i], GL_UNSIGNED_BYTE, imageData);
			stbi_image_free(imageData);
		}
		else { std::cout << "Failed to load CubemapTexture[" << i << "] with stbi_failure_reason as: \n" << stbi_failure_reason() << std::endl; stbi_image_free(imageData); }
	}

	// Texture params
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Unbind
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	stbi_set_flip_vertically_on_load(false);
}

void CubemapTexture::Clear()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	if (glIsTexture(this->textureID) == GL_TRUE) {
		glDeleteTextures(1, &this->textureID);
	}

	this->paths.clear();
	this->paths = std::vector<std::string>{ "", "", "", "", "", "" };

	this->widths			= std::vector<int>{ 0, 0, 0, 0, 0, 0 };
	this->heights			= std::vector<int>{ 0, 0, 0, 0, 0, 0 };
	this->nrChannelsList	= std::vector<int>{ 0, 0, 0, 0, 0, 0 };
	this->internalFormats	= std::vector<int>{ 0, 0, 0, 0, 0, 0 };
	this->formats			= std::vector<int>{ 0, 0, 0, 0, 0, 0 };
}

std::string CubemapTexture::GetPath(int i)
{
	return this->paths[i];
}

std::vector<std::string> CubemapTexture::GetPaths()
{
	return this->paths;
}

unsigned int CubemapTexture::GetTextureID() const		{ return this->textureID; }

std::vector<int> CubemapTexture::GetWidths()			{ return this->widths; }

std::vector<int> CubemapTexture::GetHeights()			{ return this->heights; }

std::vector<int> CubemapTexture::GetFormats()			{ return this->formats; }

std::vector<int> CubemapTexture::GetInternalFormats()	{ return this->internalFormats; }

std::vector<int> CubemapTexture::GetNrChannelsList()	{ return this->nrChannelsList; }

int CubemapTexture::GetWidth(int i)						{ return ((i < 6 && i >= 0) ? this->widths[i] : this->widths[5]); }

int CubemapTexture::GetHeight(int i)					{ return ((i < 6 && i >= 0) ? this->heights[i] : this->heights[5]); }

int CubemapTexture::GetInternalFormat(int i)			{ return ((i < 6 && i >= 0) ? this->internalFormats[i] : this->internalFormats[5]); }

int CubemapTexture::GetFormat(int i)					{ return ((i < 6 && i >= 0) ? this->formats[i] : this->formats[5]); }

int CubemapTexture::GetNrChannels(int i)				{ return ((i < 6 && i >= 0) ? this->nrChannelsList[i] : this->nrChannelsList[5]); }