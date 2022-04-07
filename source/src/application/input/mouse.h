/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 24-07-2021 21:09:09                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 05-12-2021 01:14:34                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>

namespace Nocturn
{
    struct Mouse
    {
    public:
        static void cursorPosCallback(GLFWwindow *window, const double x, const double y);
        static void mouseButtonCallback(GLFWwindow *window, const int button, const int action, const int mods);
        static void mouseWheelCallback(GLFWwindow *window, const double dx, const double dy);

        static double getDx();
        static double getDy();

        static double getX();
        static double getY();

    private:
        static double m_x;
        static double m_y;

        static double m_dx;
        static double m_dy;

        static double m_scrollDx;
        static double m_scrollDy;

        static double m_lastx;
        static double m_lasty;

        static bool m_firstMouse;
        static bool m_buttons[]; // button state array (true for down, false for up)
        static bool m_buttonsChanged[];
    };
}
#endif