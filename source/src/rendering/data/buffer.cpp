#include "buffer.h"

namespace Nocturn::rendering
{
    Buffer::Buffer() noexcept {}

    Buffer::Buffer(const uint32_t target) noexcept : m_target(target) {}

    void Buffer::generate() noexcept
    {
        glGenBuffers(1, &m_id);
    }

    void Buffer::bind() const noexcept
    {
        glBindBuffer(m_target, m_id);
    }

    void Buffer::clear() const noexcept
    {
        glBindBuffer(m_target, 0);
    }

    void Buffer::cleanup() noexcept
    {
        glDeleteBuffers(1, &m_id);
    }
}