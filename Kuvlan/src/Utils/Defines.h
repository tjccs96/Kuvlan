#pragma once

#if _WIN32 || _WIN64
#define PLATFORM_WINDOWS
#else
#if __linux__
#define PLATFORM_LINUX
#else
#error "Unsuported platform"
#endif
#endif

#ifdef PLATFORM_WINDOWS
#define FORCEINLINE __forceinline;
#define FORCENOINLINE __declspec(noinline);
#endif

// Assertions
#define ASSERTIONS_ENABLED
#ifdef ASSERTIONS_ENABLED
#include <iostream>

#if _MSC_VER
#include <intrin.h>
#define debug_break() __debugbreak();
#else
#define debug_break() __asm { int 3 }
#endif

#define ASSERT(expr) { \
	if( expr ) { \
	} else { \
		report_assertion_failure(#expr, "", __FILE__, __LINE__); \
		debug_break(); \
	} \
}

#define ASSERT_MSG(expr, message) { \
	if( expr ) { \
	} else { \
		report_assertion_failure(#expr, message, __FILE__, __LINE__); \
		debug_break(); \
	} \
}

#ifdef _DEBUG
#define ASSERT_DEBUG(expr) { \
	if( expr ) { \
	} else { \
		report_assertion_failure(#expr, "", __FILE__, __LINE__); \
		debug_break(); \
	} \
}
#else
#define ASSERT_DEBUG(expr) 
#endif

#else
#define ASSERT(expr)
#define ASSERT_MSG(expr, message)
#define ASSERT_DEBUG(expr)
#endif


FORCEINLINE void report_assertion_failure(const char* expression, const char* message, const char* file, int line)
{
	std::cerr << "Assertion Failure: " << expression << ", message: '" << message << "', in file: " << file <<
		", line: " << line << "\n";
}