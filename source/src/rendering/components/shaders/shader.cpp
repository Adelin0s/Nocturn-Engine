#include "rendering/components/shaders/shader.h"

namespace Nocturn
{
    Shader::Shader(const char *vertexPath, const char *fragmentPath)
    :   m_vertexPath                       (vertexPath)
    ,   m_fragmentPath                     (fragmentPath)
    { }

    void Shader::init()
    {
        std::string vertexCode;
        std::string fragmentCode;

        std::ifstream vertexShaderFile;
        std::ifstream fragmentShaderFile;

        vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            //open files
            vertexShaderFile.open(m_vertexPath);
            fragmentShaderFile.open(m_fragmentPath);

            std::stringstream vertexShaderStream, fragmentShaderStream;
            vertexShaderStream << vertexShaderFile.rdbuf();
            fragmentShaderStream << fragmentShaderFile.rdbuf();

            vertexShaderFile.close();
            fragmentShaderFile.close();

            vertexCode = vertexShaderStream.str();
            fragmentCode = fragmentShaderStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char *vertexShaderCode = vertexCode.c_str();
        const char *fragmentShaderCode = fragmentCode.c_str();

        uint32_t vertex, fragment;

        //vertex_shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        //fragment_shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        //link program
        m_id = glCreateProgram();
        glAttachShader(m_id, vertex);
        glAttachShader(m_id, fragment);
        glLinkProgram(m_id);
        checkCompileErrors(m_id, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Shader::activate()
    {
        glUseProgram(m_id);
    }

    void Shader::setBool(const std::string &name, const bool value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), int(value));
    }

    void Shader::setInt(const std::string &name, const int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::setFloat(const std::string &name, const float value) const
    {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void Shader::setVec2(const std::string &name, const float value1, const float value2)
    {
        glUniform2f(glGetUniformLocation(m_id, name.c_str()), value1, value2);
    }

    void Shader::setVec2(const std::string &name, const glm::vec2 &value)
    {
        glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void Shader::setVec3(const std::string &name, const glm::vec3 &value)
    {
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }

    void Shader::set3Float(const std::string &name, float value1, float value2, float value3) const
    {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), value1, value2, value3);
    }

    void Shader::set4Matrix(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    uint32_t Shader::getId() const noexcept
    {
        return m_id;
    }

    void Shader::cleanup() const
    {
        glDeleteProgram(m_id);
    }

    void Shader::checkCompileErrors(uint32_t shader, const std::string &type)
    {
        int succes;
        char log[512];
        if (type == "PROGRAM")
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &succes);
            if (!succes)
            {
                glGetProgramInfoLog(shader, 512, NULL, log);
                std::cerr << "ERROR_PROGRAM_LINKING::LINKING_FAILED\n " << log << std::endl;
            }
        }
        else
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &succes);
            if (!succes)
            {
                glGetShaderInfoLog(shader, 512, NULL, log);
                std::cerr << "ERROR_" << type << "_SHADER::COMPILATION_FAILED\n " << log << std::endl;
            }
        }
    }
}