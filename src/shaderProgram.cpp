#include "include/shaderProgram.hpp"

namespace ignition {
    ShaderProgram::ShaderProgram(const std::filesystem::path &shadersDir, const std::filesystem::path &vertexShaderFilename, const std::filesystem::path &fragmentShaderFilename) {
        std::filesystem::path fullShadersPath = Filesystem::getExecutableDir() / shadersDir;
        
        if (GLAD_GL_ARB_shading_language_include) loadShaderIncludes(fullShadersPath);

        std::string vertexCode = loadShader(fullShadersPath / vertexShaderFilename);
        std::string fragmentCode = loadShader(fullShadersPath / fragmentShaderFilename);

        GLuint vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
        GLuint fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

        programID = glCreateProgram();

        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);

        glLinkProgram(programID);

        GLint success;
        
        glGetProgramiv(programID, GL_LINK_STATUS, &success);

        if (!success) {
            char infoLog[512];

            glGetProgramInfoLog(programID, 512, nullptr, infoLog);

            std::cerr << "Error linking shader program:\n" << infoLog << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    ShaderProgram::~ShaderProgram() {
        glDeleteProgram(programID);
    }

    void ShaderProgram::use() const {
        glUseProgram(programID);
    }

    void ShaderProgram::setUniform(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    }

    void ShaderProgram::setUniform(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }

    void ShaderProgram::setUniform(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
    }

    void ShaderProgram::setUniform(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
    }

    void ShaderProgram::setUniform(const std::string &name, const glm::mat4 &value) const {
        glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void ShaderProgram::loadShaderIncludes(const std::filesystem::path &shadersPath) {
        if (!std::filesystem::exists(shadersPath) || !std::filesystem::is_directory(shadersPath)) {
            std::cerr << "Directory not found: " << shadersPath << std::endl;
            return;
        }

        for (const auto &entry : std::filesystem::recursive_directory_iterator(shadersPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".glsl") {
                std::string relativePath = Filesystem::normalizePath(entry.path().lexically_relative(shadersPath));
                std::string virtualPath = virtualRoot + relativePath;
                std::string includeCode = loadShader(entry.path());

                glNamedStringARB(GL_SHADER_INCLUDE_ARB, virtualPath.size(), virtualPath.c_str(), includeCode.size(), includeCode.c_str());
            }
        }
    }

    GLuint ShaderProgram::compileShader(const std::string &source, GLenum shaderType) {
        GLuint shader = glCreateShader(shaderType);

        const char *src = source.c_str();

        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            char infoLog[512];

            glGetShaderInfoLog(shader, 512, nullptr, infoLog);

            std::cerr << "Error compiling shader:\n" << infoLog << std::endl;
        }

        return shader;
    }

    std::string ShaderProgram::loadShader(const std::filesystem::path &shaderPath) {
        std::ifstream file(shaderPath);

        if (!file.is_open()) {
            std::cerr << "Error reading shader file: " << shaderPath << std::endl;
            return "";
        }

        std::stringstream shaderCode;

        shaderCode << file.rdbuf();

        return shaderCode.str();
    }
}
