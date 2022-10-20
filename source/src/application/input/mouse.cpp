#include "application/input/mouse.h"

namespace Nocturn
{

    bool Mouse::m_firstMouse = true;

    double Mouse::m_x = 0;
    double Mouse::m_y = 0;

    double Mouse::m_dx = 0;
    double Mouse::m_dy = 0;

    double Mouse::m_lastx = 0;
    double Mouse::m_lasty = 0;

    double Mouse::m_scrollDx = 0;
    double Mouse::m_scrollDy = 0;

    bool Mouse::m_buttons[GLFW_MOUSE_BUTTON_LAST] = {0};
    bool Mouse::m_buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = {0};

    void Mouse::CursorPosCallback(GLFWwindow *window, const double x, const double y)
    {
        m_x = x;
        m_y = y;

        if (m_firstMouse)
        {
            m_lastx = x;
            m_lasty = y;
            m_firstMouse = false;
        }

        m_dx = x - m_lastx;
        m_dy = m_lasty - y; // y coord are inverted
        m_lastx = x;
        m_lasty = y;
    }

    void Mouse::MouseButtonCallback( const int button, const int action )
    {
        if (action == GLFW_PRESS)
        {
            if (!m_buttons[button])
            {
                m_buttons[button] = true;
            }
        }
        else
        {
            m_buttons[button] = false;
        }
        m_buttonsChanged[button] = action != GLFW_REPEAT;
    }

    void Mouse::MouseWheelCallback( GLFWwindow *window, const double dx, const double dy )
    {
        Mouse::m_scrollDx = 0;
        Mouse::m_scrollDy = 0;
    }

    double Mouse::getX()
    {
        return m_x;
    }

    double Mouse::getY()
    {
        return m_y;
    }

    double Mouse::getDx()
    {
        const auto temp = m_dx;
        m_dx = 0;
        return temp;
    }

    double Mouse::getDy()
    {
        const auto temp = m_dy;
        m_dy = 0;
        return temp;
    }
}