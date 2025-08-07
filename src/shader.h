#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
class Shader {
public:
    static ShaderUPtr CreateFromFile(const std::string& filename,
        GLenum shaderType);

    ~Shader();
    uint32_t Get() const { return m_shader; }    

private:
    Shader() {}
    bool LoadFile(const std::string& filename, GLenum shaderType);
    uint32_t m_shader { 0 };
};

#endif // __SHADER_H__

//생성자가 private -> new로 생성 막음
//static function(CreateFromFile) 함수만으로 생성하도록

//Get()만 있는 이유 -> shader object 생성 관리는 shader 내부에서만 관리