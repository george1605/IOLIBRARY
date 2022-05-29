#pragma once
#include "core.h"
#if !defined(__APPLE__) && !defined(__ANDROID__)
	#ifdef _MSC_VER
		#pragma warning("This platform is not supported or this device is not mobile!")
	#else
		//
	#endif
	namespace io
	{
		int mobile_dev = -1;
	}
#endif

#ifdef __APPLE__

#endif

#ifdef __ANDROID__
#include "arm.h"

namesapce io
{

}
#endif