/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 31-07-2021 14:51:46                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 21-11-2021 00:02:38                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/glm.hpp>

namespace Nocturn::rendering
{
    using Vec3_t = glm::vec3;
    using Coords_t = float;
    using Indices_t = uint32_t;

    struct Mesh
    {
        std::vector<Coords_t> vertices;
        std::vector<Coords_t> textures;
        std::vector<Indices_t> indices;

        inline void clear()
        {
            vertices.clear();
            textures.clear();
            indices.clear();
        }

        inline void shrink()
        {
            vertices.shrink_to_fit();
            textures.shrink_to_fit();
            indices.shrink_to_fit();
        }
    };
}
#endif
