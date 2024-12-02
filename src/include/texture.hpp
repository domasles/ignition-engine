#pragma once

#include "glad/glad.h"
#include "filesystem.hpp"

#include <string>
#include <iostream>

namespace ignition {
    class Texture {
        public:
            Texture(const std::filesystem::path &texturePath);
            ~Texture();

            void bind(unsigned int unit = 0) const;
            void unbind() const;

            bool isLoaded() const { return loaded; }

        private:
            int width, height, nrChannels, format;
            bool loaded;
        
            GLuint textureID;
    };
}
