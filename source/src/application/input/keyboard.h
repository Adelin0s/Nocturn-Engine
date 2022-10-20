#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>

namespace Nocturn
{
    struct Keyboard
    {
    public:
		static void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );
		static bool key( int key );
		static bool keyChanged( int key );
		static bool keyWentUp( int key );
		static bool keyWentDown( int key );

    private:
        static bool m_keys[];
        static bool m_keysChanged[];
    };
}
#endif