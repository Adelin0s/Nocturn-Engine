/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 08-07-2021 14:48:26                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 17-01-2022 14:13:25                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#include "application/application.h"

int main( )
{
	Nocturn::Application::Init( );
	Nocturn::Application::Run( );
	Nocturn::Application::Free( );

	return 0;
}