#ifndef RSTATUS_H
#define RSTATUS_H

#include "core/platform/platform.h"
#include "core/types/typedef.hpp"

namespace Nocturn
{
	using RStatusType = uint8;

	enum class RStatus : RStatusType
	{
		Succes = 0
		,	Fail
		,	SystemTerminated
		,	InvalidArguments
		, MAX
	};

	constexpr RStatus RSucces				{ RStatus::Succes };
	constexpr RStatus RFail					{ RStatus::Fail };
	constexpr RStatus RSystemTerminated		{ RStatus::SystemTerminated };
	constexpr RStatus RInvalidArguments		{ RStatus::InvalidArguments };

	//FORCE_INLINE bool operator !(const RStatus& status)
	//{
	//	return status != RSucces;
	//}

	//FORCE_INLINE bool RStatusToBool(const RStatus& status)
	//{
	//	return status == RSucces;
	//}
}
#endif