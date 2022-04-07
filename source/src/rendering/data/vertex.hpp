/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 10-09-2021 10:29:58                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 25-10-2021 20:01:36                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <glm/glm.hpp>

namespace Nocturn::rendering
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;

        static const std::vector<struct Vertex> genList(const float *vertices, const unsigned int noVertices) noexcept
        {
            std::vector<Vertex> ret_vec(noVertices);
            int stride = sizeof(Vertex) / sizeof(float);

            for (unsigned int i = 0; i < noVertices; i++)
            {
                ret_vec[i].position = glm::vec3(
                    vertices[i * stride + 0],
                    vertices[i * stride + 1],
                    vertices[i * stride + 2]);
                ret_vec[i].texCoords = glm::vec2(
                    vertices[i * stride + 3],
                    vertices[i * stride + 4]);
            }

            return ret_vec;
        }
    };
}

#endif // VERTEX_H