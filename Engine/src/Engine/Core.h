#pragma once

#include <memory>

#define ENGINE_API 

#define EG_ENABLE_ASSERTS

#ifdef  EG_ENABLE_ASSERTS
    #define EMBED_BREAKPOINT  asm volatile ("int3;")
    #define EG_ASSERT(x, ...) {if(!x) {EG_ERROR("Assertion Failed:{0}", __VA_ARGS__); EMBED_BREAKPOINT;}}
    #define EG_CORE_ASSERT(x, ...) {if(!x) {EG_CORE_ERROR("Assertion Failed:{0}", __VA_ARGS__); EMBED_BREAKPOINT;}}
#else
    #define EG_ASSERT(x, ...)
    #define EG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1<<x) 

#define EG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1 )

namespace Engine{

    template<typename T>
    using Scope = std::unique_ptr<T>;
    
    template<typename T>
    using Ref = std::shared_ptr<T>;

}