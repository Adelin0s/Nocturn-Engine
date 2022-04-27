/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 08-07-2021 14:48:26                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 17-01-2022 14:13:25                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

//#include "application/application.h"

#include <iostream>
#include "core/async/task.h"

using namespace Nocturn;

std::mutex m;

std::atomic_int count = 0;

void f( )
{
	std::cout << std::this_thread::get_id( ) << ' ';
	++count;
}

int main( )
{
	TaskSystem taskSystem( 8 );

	for( int i = 0; i < 100; i++ )
	{
		PriorityTask task( [ = ]( )
						   { f( ); },
						   ETaskPriorityLevel::Low );
		taskSystem.Async( std::move( task ) );
	}

	taskSystem.PrintTaskEachQueue( );

	taskSystem.ForceQuit( );

	// Nocturn::Application::init( );
	// Nocturn::Application::run( );
	// Nocturn::Application::free( );

	return 0;
}