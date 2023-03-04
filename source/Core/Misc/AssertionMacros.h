#pragma once

#include <string>

#include "Core/Types/typedef.hpp"

#ifdef _WIN32
	#define __FILENAME__	Log::ShortFileName(__FILE__, sizeof(__FILE__) - 1)
#endif

#define NOCTURN_INFO_IMPL(fmt, ...) Log::LogWrite( Log::Info, __FILENAME__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ );
#define NOCTURN_DEBUG_IMPL(fmt, ...) Log::LogWrite( Log::Debug, __FILENAME__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ );
#define NOCTURN_WARNING_IMPL(fmt, ...) Log::LogWrite( Log::Warning, __FILENAME__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ );
#define NOCTURN_ERROR_IMPL(fmt, ...) Log::LogWrite( Log::Error, __FILENAME__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ );

#ifdef _WIN32
	#define Log( fmt, ... ) NOCTURN_INFO_IMPL( fmt, __VA_ARGS__ )
	#define LogDebug( fmt, ... ) NOCTURN_DEBUG_IMPL( fmt, __VA_ARGS__ )
	#define LogWarning( fmt, ... ) NOCTURN_WARNING_IMPL( fmt, __VA_ARGS__ )
	#define LogError( fmt, ... ) NOCTURN_ERROR_IMPL( fmt, __VA_ARGS__ )
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

	void LogWrite( ELevel Level, const char *FileName, const char *FunctionName, uint32_t LineNumber, const char *Format, ...);
}