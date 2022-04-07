/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 11-09-2021 18:48:29                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 18-09-2021 20:31:24                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef STATES_H
#define STATES_H

#include <memory>

namespace Nocturn::core::States
{
    template <typename T>
    bool isActive(T& states, const int target)
    {
        /**
         * 10101101    states 
         * 00001000&   1<<3 target 
         * --------
         * 00001000 == 1<<3
        */
        return (states & (1 << target)) == (1 << target);
    }

    template <typename T>
    void activate(T& states, const int target)
    {
        /**
         * 10101101
         * 00010000|
         * --------
         * 10111101
         */
        states |= (1 << target);
    }

    template <typename T>
    void uniquelyActivate(T& states, const int target)
    {
        /**
         * 10000000
         * 00001000|
         * --------
         * 10001000
         * 00001000&
         * --------
         * 00001000
         */
        activate(states, target); // activate state first
        states &= (1 << target); // deactivate others
    }

    template <typename T>
    void deactivate(T& states, const int target)
    {
        /**
         * 11001000
         * 11110111&
         * --------
         * 11000000
         */
        states &= ~(1 << target);
    }

    template <typename T>
    void tooggle(T& states, const int target)
    {
        /**
         * 11000010 <--
         * 00001000^   |
         * --------    |
         * 11001010    |
         * 00001000^   |
         * --------    |
         * 11000010----
         */
        states ^= (1 << target);
    }
}

#endif