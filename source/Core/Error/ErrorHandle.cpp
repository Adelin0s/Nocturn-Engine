#include "ErrorHandle.h"

namespace Nocturn::core
{
    void GLClearError()
    {
        while (glGetError() != GL_NO_ERROR)
            ;
    }

    void GLCheckError()
    {
        while (GLenum error_code = glGetError())
        {
            std::string error_string;

            switch (error_code)
            {
            case GL_INVALID_ENUM:
                error_string = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error_string = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error_string = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error_string = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error_string = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error_string = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_string = "INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                error_string = "NO_ERROR";
                break;
            }

            std::cerr << "[OpenGL Error] " << error_code << " " << error_string << std::endl;
        }
    }
}