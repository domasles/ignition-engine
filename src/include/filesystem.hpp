#pragma once

#include <string>
#include <stdexcept>
#include <filesystem>

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <unistd.h>
#endif

namespace ignition {
    class Filesystem {
        public:
            static std::filesystem::path getExecutableDir();
            static std::string normalizePath(const std::filesystem::path &path);
    };
}
