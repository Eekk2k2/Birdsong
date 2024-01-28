#include "Texture.h"

Texture::Texture(int WRAPPING, const char* filename, bool flipImage, std::string name)
{
    this->texture = 0;

    stbi_set_flip_vertically_on_load(flipImage); 

    this->width = 0, this->height = 0, this->nrChannels = 0;
    unsigned char* data = stbi_load(filename, &this->width, &this->height, &this->nrChannels, 0);
    if (data)
    {
        glGenTextures(1, &this->texture);
        glBindTexture(GL_TEXTURE_2D, this->texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int INTERNAL_FORMAT = 0, FORMAT = 0;
        switch (this->nrChannels)
        {
        case 1:
            INTERNAL_FORMAT = GL_RED;
            FORMAT = GL_RED;
            break;
        case 2:
            INTERNAL_FORMAT = GL_RED;
            FORMAT = GL_RED;
            break;
        case 3:
            INTERNAL_FORMAT = GL_SRGB;
            FORMAT = GL_RGB;
            break;
        case 4:
            INTERNAL_FORMAT = GL_SRGB_ALPHA;
            FORMAT = GL_RGBA;
            break;
        default:
            INTERNAL_FORMAT = GL_RED;
            FORMAT = GL_RED;
            break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, INTERNAL_FORMAT, width, height, 0, FORMAT, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else { std::cout << "Failed to load texture" << std::endl; }

    // Finishes
	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(false);
    this->name = name;
}

Texture::~Texture() { glDeleteTextures(1, &texture); }

