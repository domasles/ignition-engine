#include "include/filesystem.hpp"

namespace ignition {
	std::filesystem::path Filesystem::getExecutableDir() {
		char buffer[1024];

		#ifdef _WIN32
			GetModuleFileNameA(nullptr, buffer, sizeof(buffer));
		#elif __linux__
			ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer));

			if (count == -1) throw std::runtime_error("Failed to get executable path");

			buffer[count] = '\0';
		#else
			throw std::runtime_error("Unsupported platform");
		#endif

		return std::filesystem::path(buffer).parent_path();
	}

	std::string Filesystem::normalizePath(const std::filesystem::path &path) {
		return path.generic_string();
	}
}
