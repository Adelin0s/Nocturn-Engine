/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 07-09-2021 12:46:55                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 05-12-2021 19:59:51                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include <glad/glad.h>

#include <map>

#include "rendering/data/buffer.h"

namespace Nocturn::rendering
{
    class VertexArray
    {
    public:
        VertexArray() noexcept = default;

        ~VertexArray() noexcept = default;

        void generate() noexcept;
        static void bind() noexcept;
        void cleanup() noexcept;
        void draw(const GLenum mode, const int32_t first, const uint32_t count, const uint32_t instance_count = 1);

        Buffer &operator[](const char *key) noexcept;

        void print_id() { std::cout << m_id << '\n'; }

        static void clear();

    private:
        std::map<const char *, Buffer> m_buffers;
        static uint32_t m_id;
    };
}

#endif // VERTEX_ARRAY_H