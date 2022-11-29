#pragma once

#include <memory>
#include <vector>
# ifdef FR_PLATFORM_WINDOWS
# if FR_DYNAMIC_LINK
       #ifdef FR_BUILD_DLL
            #define FORGE_API __declspec(dllexport)
        
       #else  
            #define FORGE_API __declspec(dllimport)

       #endif
#else
       #define FORGE_API
#endif
#else 
     #error Forge Engine only supports Windows for now

#endif
#define BIT(x) (1 <<x )


#define FR_BIND_EVENT_FN(fn) std::bind(&fn, this ,std::placeholders::_1 )

#define FR_ENABLE_ASSERTS
#define FR_DEBUGBREAK();
#define FR_EXPAND_MACRO(x) x
#define FR_STRINGIFY_MACRO(x) #x

#define FString std::string 
#define FContainer std::array
namespace Forge
{
  
//    template<typename T>
    //using FVector = std::vector<T>;

    template<typename T>
    using FScope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr FScope<T> FCreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using FRef = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr FRef<T> FCreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}
#include "core/log/log.h"
#include "core/log/assertion.h"
#include <stddef.h>

#ifndef MIN
#define MIN(m_a, m_b) (((m_a) < (m_b)) ? (m_a) : (m_b))
#endif

#ifndef MAX
#define MAX(m_a, m_b) (((m_a) > (m_b)) ? (m_a) : (m_b))
#endif

#ifndef CLAMP
#define CLAMP(m_a, m_min, m_max) (((m_a) < (m_min)) ? (m_min) : (((m_a) > (m_max)) ? m_max : m_a))
#endif
