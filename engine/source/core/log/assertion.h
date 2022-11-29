#pragma once
#include "core/core.h"
#include "core/log/log.h"
#include <filesystem>

#ifdef FR_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define FR_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { FR##type##ERROR(msg, __VA_ARGS__); FR_DEBUGBREAK(); } }
#define FR_INTERNAL_ASSERT_WITH_MSG(type, check, ...) FR_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define FR_INTERNAL_ASSERT_NO_MSG(type, check) FR_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", FR_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define FR_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define FR_INTERNAL_ASSERT_GET_MACRO(...) FR_EXPAND_MACRO( FR_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, FR_INTERNAL_ASSERT_WITH_MSG, FR_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define FR_ASSERT(...) FR_EXPAND_MACRO( FR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define FR_CORE_ASSERT(...) FR_EXPAND_MACRO( FR_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define FR_ASSERT(...)
#define FR_CORE_ASSERT(...)
#endif

