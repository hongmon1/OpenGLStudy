#include "program.h"

ProgramUPtr Program::Create(const std::vector<ShaderPtr>& shaders) 
{
    auto program = ProgramUPtr(new Program());
    if (!program->Link(shaders))
        return nullptr;
    return std::move(program);
}

bool Program::Link(const std::vector<ShaderPtr>& shaders) 
{
    m_program = glCreateProgram(); //opengl program object 생성
    for (auto& shader: shaders)
        glAttachShader(m_program, shader->Get()); //program에 shader 붙이기
    glLinkProgram(m_program); //program 링크

    int success = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success); //program 링크 상태 확인
    if (!success) 
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to link program: {}", infoLog);
        return false;
    }

    return true;
}

void Program::Use() const 
{
    glUseProgram(m_program);
}

Program::~Program() 
{
    if (m_program) 
    {
        glDeleteProgram(m_program);
    }
}
