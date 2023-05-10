// =====================================================================
//   @ Author: Cucorianu Eusebiu Adelin                                                                                      
//   @ Create Time: 08-07-2021 14:48:26  
//   @ Contact: cucorianu.adelin@protonmail.com                                                                                                                          
//   @ Modified time: 13-10-2022 5:53 PM                                                                                                                                    
//   @ Description:                                                                                                                                                                                
// =====================================================================

#include "application/application.h"
#include "Core/core.h"

int main( )
{
	const auto Status = Log::Initialize();
	if( Status == false )
	{
		printf( "Failed to Initialize NocturnLog!" );
		return 0;
	}

	Nocturn::Application::Init( );

	Nocturn::Application::Run( );

	Nocturn::Application::Free( );

	return 0;
}