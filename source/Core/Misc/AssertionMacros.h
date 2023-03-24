#pragma once

#include <format>
#include <iostream>
#include <string>

#include "Core/core.h"

#include "Core/Platform/platform.h"


#ifdef _WIN32
	#define __FILENAME__	Log::ShortFileName(__FILE__, sizeof(__FILE__) - 1)
#endif

#define NOCTURN_INFO_IMPL(fmt, ...) Log::LogWrite( Log::Info, __FILENAME__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ );
#define NOCTURN_DEBUG_IMPL(fmt, ...) Log::LogWrite( Log::Debug, __FILENAME__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ );
#define NOCTURN_WARNING_IMPL(fmt, ...) Log::LogWrite( Log::Warning, __FILENAME__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ );
#define NOCTURN_ERROR_IMPL(fmt, ...) Log::LogWrite( Log::Error, __FILENAME__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ );
#define NOCTURN_LOG_SCREEN_IMPL(fmt, ...) Log::LogWriteScreen( fmt, __VA_ARGS__ );

#ifdef _WIN32
	#define Log( fmt, ... ) NOCTURN_INFO_IMPL( fmt, __VA_ARGS__ )
	#define LogDebug( fmt, ... ) NOCTURN_DEBUG_IMPL( fmt, __VA_ARGS__ )
	#define LogWarning( fmt, ... ) NOCTURN_WARNING_IMPL( fmt, __VA_ARGS__ )
	#define LogError( fmt, ... ) NOCTURN_ERROR_IMPL( fmt, __VA_ARGS__ )

	#define LogScreen( fmt, ... ) NOCTURN_LOG_SCREEN_IMPL( fmt, __VA_ARGS__ );

    #define Assert(expression) \
        if( false == !!( expression ) ) UNLIKELY \
        { \
            Log::AssertFailHandler( #expression, __FILE__, __LINE__ ); \
        }\

    #define AssertInfo(expression, msg) \
        if( false == !!( expression ) ) UNLIKELY \
        { \
            Log::AssertFailHandler( #expression, __FILE__, __LINE__, msg ); \
        }
#else
	#define Log( fmt, ... ) printf( fmt, _VA_ARGS__ )
	#define LogDebug( fmt, ... ) printf( fmt, _VA_ARGS__ )
	#define LogWarning( fmt, ... ) printf( fmt, _VA_ARGS__ )
	#define LogError( fmt, ... ) printf( fmt, _VA_ARGS__ )
#endif

#ifdef _WIN32
	#define Check(expr) \
	{ \
		if(!(expr)) \
		{ \
			LogWrite(Log::Error, __FILENAME__, __FUNCTION__, __LINE__, "Failed"); \
		} \
	} 
#else
#define check(expr) \
	{ \
		if(!(expr)) \
		{ \
			printf("NocturnLog: Failed!");
		} \
	} 
#endif

namespace Log
{
	typedef void* NFileHandle;

	inline NFileHandle FileHandle{ nullptr };

	constexpr const char* CLogName = "nocturn_log.txt";

	extern thread_local std::array<char, 4098> AssertWorkBuffer;

	enum ELevel
	{
		Debug = 0
		,	Info
		,	Warning
		,	Error
		, None
	};

	struct NLogData
	{
		ELevel Level;
		char* Message;
		int32 LogLen;
		int32 LineNumber;
		const char* Condition;
		const char* FileName;
		const char* FunctionName;
		const char* Format;
		void* Args;
	};

	constexpr const char* ShortFileName(const char* String, const uint32 Length)
	{
		for (uint32 i = Length - 1; i > 0 ; --i)
		{
			if (String[i] == '\\' || String[i] == '/')
			{
				return String + i + 1;
			}
		}
		return "";
	}

	void FormatLog(const NLogData& LogData, std::string& Buffer);

	bool Initialize();

	// TODO: Exclude <iostream> from header
	template< typename... TArgs >
	void LogWriteScreen( std::_Fmt_string< TArgs... > fmt, TArgs &&...Args )
	{
		std::cout << std::format( "[{} : {}]: ", __FILE__, __LINE__ );
		std::cout << std::format( fmt, std::forward< TArgs >( Args )... );
		std::cout << '\n';
	}

    NOINLINE NORETURN inline void AssertFailHandler( const char* InExpressionAsString, const char* InFileName, size_t LineNumber ) noexcept
    {
        ( void )snprintf( AssertWorkBuffer.data(), AssertWorkBuffer.size(), "\u001b[31mAssert \"%s\" failed!\nAt:%s:%llu \n\u001b[37m", InExpressionAsString, InFileName, LineNumber );
        ( void )printf( AssertWorkBuffer.data() );
        BREAK();
        abort();
    }
    
    NOINLINE NORETURN inline void AssertFailHandler( const char* InExpressionAsString, const char* InFileName, size_t LineNumber, const char* InMessage ) noexcept
    {
        ( void )snprintf( AssertWorkBuffer.data(), AssertWorkBuffer.size(), "\u001b[31mAssert \"%s\" failed!\nAt:%s:%llu \nMessage:%s\n\u001b[37m", InExpressionAsString, InFileName, LineNumber, InMessage );
        ( void )printf( AssertWorkBuffer.data() );
        BREAK();
        abort();
    }

	void LogWrite( ELevel Level, const char *FileName, const char *FunctionName, uint32 LineNumber, const char *Format, ...);
}