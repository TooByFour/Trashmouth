#pragma once

#include <filesystem>
#include <glad/glad.h>
#include <string>

#include <glm/glm.hpp>

/**
 * Following LearnOpenGL
 */
namespace TM
{
    namespace Shader
    {
        uint32_t CreateShader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);
    }
}
