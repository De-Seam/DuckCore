#pragma once

#define EXPAND_MACRO(x) x

#define BREAKPOINT() __debugbreak()

void gLog(const char* inMessage) {}

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define HZ_INTERNAL_ASSERT_IMPL(check, msg, ...) { if(!(check)) { gLog(msg); BREAKPOINT(); } }
#define HZ_INTERNAL_ASSERT_WITH_MSG(check, ...) HZ_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define HZ_INTERNAL_ASSERT_NO_MSG(check) HZ_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", HZ_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define HZ_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define HZ_INTERNAL_ASSERT_GET_MACRO(...) EXPAND_MACRO( HZ_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, HZ_INTERNAL_ASSERT_WITH_MSG, HZ_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define gAssert(...) EXPAND_MACRO( HZ_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )