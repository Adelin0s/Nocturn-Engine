#include "rendering/data/vertexarray.h"

namespace Nocturn::rendering
{
    uint32_t VertexArray::m_id = 1;

    void VertexArray::generate() noexcept
    {
        glGenVertexArrays(1, &m_id);
    }

    void VertexArray::bind() noexcept
    {
        glBindVertexArray(m_id);
    }

    void VertexArray::cleanup() noexcept
    {
        glDeleteVertexArrays(1, &m_id);
        for (auto &pair : m_buffers)
            pair.second.cleanup();
    }

    void VertexArray::draw(const GLenum mode, int32_t first, const uint32_t count, const uint32_t instance_count)
    {
        glDrawArraysInstanced(mode, first, count, instance_count);
    }

    Buffer &VertexArray::operator[](const char *key) noexcept
    {
        return m_buffers[key];
    }

    void VertexArray::clear()
    {
        glBindVertexArray(0);
    }
}