#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>

namespace Nocturn
{
    struct Keyboard
    {
    public:
        static void keyCallback(GLFWwindow *window, const int key, const int scancode, const int action, const int mods);
        static bool key(const int key);
        static bool keyChanged(const int key);
        static bool keyWentUp(const int key);
        static bool keyWentDown(const int key);

    private:
        static bool m_keys[];
        static bool m_keysChanged[];
    };
}
#endif