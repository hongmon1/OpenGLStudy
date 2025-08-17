#include "buffer.h"

BufferUPtr Buffer::CreateWithData(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize) 
{
    auto buffer = BufferUPtr(new Buffer());
    if (!buffer->Init(bufferType, usage, data, dataSize))
        return nullptr;
    return std::move(buffer);
}

Buffer::~Buffer() 
{
    if (m_buffer) 
    {
        glDeleteBuffers(1, &m_buffer);
    }
}

void Buffer::Bind() const 
{
    glBindBuffer(m_bufferType, m_buffer);
}

bool Buffer::Init(uint32_t bufferType, uint32_t usage, const void* data, size_t dataSize) 
{
    m_bufferType = bufferType; // verfer 타입
    m_usage = usage; // data 용도
    glGenBuffers(1, &m_buffer); // 새로운 buffer object 생성
    Bind();
    glBufferData(m_bufferType, dataSize, data, usage); //지금 사용할 buffer object 지정

    //usage
    //GL_STATIC_DRAW : 한번만 세팅해서 계속 사용
    //GL_DYNAMIC_DRAW : 데이터 계속 변경
    //GL_STREAM_DRAW : 한번만 쓰고 버림

    return true;
}
