#include "Texture2D.h"

Texture2D::Texture2D(std::string path, bool flipImage)
{
    this->path = "";

    this->width = 0;
    this->height = 0;
    this->nrChannels = 0;
    this->internalFormat = 0;
    this->format = 0;

    this->Set(path, flipImage);
}

Texture2D::~Texture2D() { this->Clear(); }

void Texture2D::Set(std::string path, bool flipImage)
{
    this->Clear();
    stbi_set_flip_vertically_on_load(flipImage);
    
    unsigned char* imageData = stbi_load(path.c_str(), &this->width, &this->height, &this->nrChannels, 0);
    if (imageData) {
        
        // Make the texture
        glGenTextures(1, &this->textureID);
        glBindTexture(GL_TEXTURE_2D, this->textureID);

        // Texture Parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Determine texture type
        switch (this->nrChannels) {
        case 1:
            this->internalFormat = GL_RED;
            this->format = GL_RED;
            break;
        case 2:
            this->internalFormat = GL_RED;
            this->format = GL_RED;
            break;
        case 3:
            this->internalFormat = GL_SRGB;
            this->format = GL_RGB;
            break;
        case 4:
            this->internalFormat = GL_SRGB_ALPHA;
            this->format = GL_RGBA;
            break;
        default:
            this->internalFormat = GL_RED;
            this->format = GL_RED;
            break;
        }

        // Register the texture data
        glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, this->width, this->height, 0, this->format, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { std::cout << "Failed to load Texture2D with stbi_failure_reason as: \n" << stbi_failure_reason() << std::endl; }

    // Finished
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(imageData);
    stbi_set_flip_vertically_on_load(false);
}

void Texture2D::Clear()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    if (glIsTexture(this->textureID) == GL_TRUE) {
        glDeleteTextures(1, &this->textureID);
    }

    this->path = "";

    this->width = 0;
    this->height = 0;
    this->nrChannels = 0;
    this->internalFormat = 0;
    this->format = 0;
}

std::string Texture2D::GetPath() { return this->path; }

unsigned int Texture2D::GetTextureID() const { return this->textureID; }

int Texture2D::GetWidth() const { return this->width; }

int Texture2D::GetHeight() const { return this->height; }

int Texture2D::GetFormat() const { return this->format;}

int Texture2D::GetInternalFormat() const { return this->internalFormat; }

int Texture2D::GetNrChannels() const { return this->nrChannels; }



