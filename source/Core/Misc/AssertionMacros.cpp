#include "AssertionMacros.h"

#define NOMINMAX
#include <windows.h>

namespace Log
{
	void FormatLog( const NLogData &LogData, std::string &Buffer )
	{
		switch( LogData.Level )
		{
			case Log::Debug:
				Buffer.append( "[Debug]\t" );
				break;
			case Log::Info:
				Buffer.append( "[Info]\t" );
				break;
			case Log::Warning:
				Buffer.append( "[Warning]\t" );
				break;
			case Log::Error:
				Buffer.append( "[Error]\t" );
				break;
			case Log::None:
				break;
		}

		Buffer.append( "[" + std::string(__TIME__) + "]" );

		Buffer.append( "[" +  std::string(LogData.FileName) + "]" );

		const auto LineNumber = std::to_string( LogData.LineNumber );
		Buffer.append( "[" + std::string(LogData.FunctionName) + ":" + LineNumber + "] - " );

		Buffer.append( LogData.Message, LogData.LogLen );

		Buffer.append( "\n" );
	}

	bool Initialize( )
	{
		FileHandle = ::CreateFileA( CLogName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );
		if( FileHandle == INVALID_HANDLE_VALUE )
		{
			printf( "Failed to CreateFileA!" );
			return false;
		}
		return true;
	}

	void LogWrite( const Log::ELevel Level, const char *FileName, const char *FunctionName, const uint32_t LineNumber, const char *Format, ... )
	{
		if( FileHandle == nullptr )
		{
			printf( "Uninitialised FileHandle!" );
			return;
		}

		Log::NLogData LogData{ };

		char Buffer[ 1024 ];

		va_list Args;
		va_start( Args, Format );
		const auto LogLen = vsnprintf( nullptr, 0, Format, Args );
		vsnprintf( Buffer, LogLen + 1, Format, Args );

		LogData.Level		 = Level;
		LogData.Message		 = Buffer;
		LogData.LogLen		 = LogLen;
		LogData.FileName	 = FileName;
		LogData.FunctionName = FunctionName;
		LogData.LineNumber	 = LineNumber;
		LogData.Format		 = Format;
		LogData.Args		 = Args;
		va_end( Args );

		std::string FormatedString;
		Log::FormatLog( LogData, FormatedString );
		DWORD nNumberOfBytesWritten;

		::WriteFile( FileHandle, FormatedString.data( ), FormatedString.length( ), &nNumberOfBytesWritten, nullptr );
		printf("%s", FileName);
	}
} // namespace Log
