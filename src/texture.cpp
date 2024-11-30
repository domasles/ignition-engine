#include "include/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

namespace ignition {
    Texture::Texture(const std::filesystem::path &texturePath) : loaded(false) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(true);

        std::string fullTexturePath = (Filesystem::getExecutableDir() / texturePath).string();

        unsigned char* data = stbi_load(fullTexturePath.c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            loaded = true;
        } else {
            std::cerr << "Failed to load texture: " << fullTexturePath << std::endl;
        }

        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &textureID);
    }

    void Texture::bind(unsigned int unit) const {
        if (loaded) {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
    }

    void Texture::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
