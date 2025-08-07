#include "shader.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType) 
{
    std::unique_ptr<Shader> shader = std::unique_ptr<Shader>(new Shader());
    if (!shader->LoadFile(filename, shaderType))
        return nullptr;
    return std::move(shader);
}

Shader::~Shader()
{
    if(m_shader)
    {
        glDeleteShader(m_shader);
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType) 
{
    std::optional<std::string> result = LoadTextFile(filename);
    if (!result.has_value()) 
    {
        return false;
    }

    std::string& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    // create and compile shader
    m_shader = glCreateShader(shaderType); //shader 오브젝트 생성
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength); // shader 소스코드 입력
    glCompileShader(m_shader); // shader 컴파일

    // check compile error
    int success = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success); //shader에 있는 정보 얻어옴
    if (!success) 
    {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    return true;
}