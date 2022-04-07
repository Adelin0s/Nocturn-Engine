#include "application/input/keyboard.h"

namespace Nocturn
{
    bool Keyboard::m_keys[GLFW_KEY_LAST] = {0};

    bool Keyboard::m_keysChanged[GLFW_KEY_LAST] = {0};

    void Keyboard::keyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods)
    {
        if (GLFW_RELEASE != action)
        {
            if (!m_keys[key])
            {
                m_keys[key] = true;
            }
        }
        else
        {
            m_keys[key] = false;
        }
        m_keysChanged[key] = action != GLFW_RELEASE;
    }

    bool Keyboard::key(const int key)
    {
        return m_keys[key];
    }

    bool Keyboard::keyChanged(const int key)
    {
        bool ret = m_keysChanged[key];
        m_keysChanged[key] = false;
        return ret;
    }

    bool Keyboard::keyWentUp(const int key)
    {
        return !m_keys[key] && keyChanged(key);
    }

    bool Keyboard::keyWentDown(const int key)
    {
        return m_keys[key] && keyChanged(key);
    }
}