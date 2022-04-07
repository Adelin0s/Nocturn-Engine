#ifndef LOGGING_H
#define LOGGING_H

namespace Nocturn::log
{
	enum class severity
	{
		trace, // lowest severity
		debug,
		info,
		warn,
		error,
		fatal // highest severity
	};
}

#endif