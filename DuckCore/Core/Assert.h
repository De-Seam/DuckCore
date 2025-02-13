#pragma once
// DuckCore includes
#include <DuckCore/Containers/String.h>

// Std includes
#include <filesystem>

#define EXPAND_MACRO(x) x

#define BREAKPOINT() __debugbreak()

#define STRINGIFY_MACRO(x) #x

#ifdef _ASSERTS

void gLogAssert(const char* inMessage);

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define INTERNAL_ASSERT_IMPL(inCheck, inMsg, ...) do { if(!(inCheck)) { gLogAssert(inMsg); BREAKPOINT(); } } while(false)

#define INTERNAL_ASSERT_WITH_MSG(inCheck, ...) INTERNAL_ASSERT_IMPL(inCheck, "Assertion '" #inCheck "' failed at " __FILE__  ":" TO_STRING(__LINE__) ": " __VA_ARGS__)
#define INTERNAL_ASSERT_NO_MSG(inCheck) INTERNAL_ASSERT_IMPL(inCheck, "Assertion '" #inCheck "' failed at " __FILE__  ":" TO_STRING(__LINE__))

#define INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define INTERNAL_ASSERT_GET_MACRO(...) EXPAND_MACRO( INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, INTERNAL_ASSERT_WITH_MSG, INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define gAssert(...) EXPAND_MACRO( INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#define gVerify(x) gAssert(x)

#else

#define gAssert(...)
#define gVerify(x) x

#endif

// #define INTERNAL_ASSERT_WITH_MSG(inCheck, ...) INTERNAL_ASSERT_IMPL(inCheck, DC::String("Assertion '") + DC::String(STRINGIFY_MACRO(inCheck)) + "' failed at " + DC::String(std::filesystem::path(__FILE__).filename().string()) + ":" + DC::gToString((uint32)__LINE__) + ": " + __VA_ARGS__)
// #define INTERNAL_ASSERT_NO_MSG(inCheck) INTERNAL_ASSERT_IMPL(inCheck, DC::String("Assertion '") + DC::String(STRINGIFY_MACRO(inCheck)) + "' failed at " + DC::String(std::filesystem::path(__FILE__).filename().string()) + ":" + DC::gToString((uint32)__LINE__))