#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef WIN32
#include <windows.h>
#endif
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <spdlog/spdlog.h>

#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr = std::unique_ptr<klassName>; \
using klassName ## Ptr = std::shared_ptr<klassName>; \
using klassName ## WPtr = std::weak_ptr<klassName>;

// ex
/*
#define CLASS_PTR(Shader) \
class Shader; \
using ShaderUPtr = std::unique_ptr<Shader>; \
using ShaderPtr = std::shared_ptr<Shader>; \
using ShaderWPtr = std::weak_ptr<Shader>;
*/

std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__