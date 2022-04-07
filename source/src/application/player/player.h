/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 01-12-2021 21:11:16                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 07-12-2021 19:38:22                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include "core/physics/rigidbody.h"

namespace Nocturn
{
    class Player
    {
        void update(const float dt);

        core::Rigidbody m_rigidbody;
    };
}

#endif 