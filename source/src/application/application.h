/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 03-12-2021 10:45:49                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 05-12-2021 21:37:02                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "application/window/window.h"

namespace Nocturn::Application
{
	void	Init( );
	void	Run( );
	void	Free( );
	Window &getWindow( );
} // namespace Nocturn::Application

#endif