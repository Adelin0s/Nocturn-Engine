/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 06-08-2021 01:57:14                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 18-09-2021 20:30:42                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef _ERROR_HANDLE_H_
#define _ERROR_HANDLE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Nocturn::core
{

    void GLClearError();
    void GLCheckError();
}

#endif