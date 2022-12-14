#pragma once
#include "egpch.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

#include "Engine/Core.h"

namespace Engine
{

    class ENGINE_API Log
    {
    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;

    public:
        static void Init();

        inline static Ref<spdlog::logger>& GetCoreLogger() {return s_CoreLogger;}
        inline static Ref<spdlog::logger>& GetClientLogger() {return s_ClientLogger;}

    };

    //Core log macros
    #define EG_CORE_TRACE(...)    ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
    #define EG_CORE_INFO(...)     ::Engine::Log::GetCoreLogger()->info (__VA_ARGS__)
    #define EG_CORE_WARN(...)     ::Engine::Log::GetCoreLogger()->warn (__VA_ARGS__)
    #define EG_CORE_ERROR(...)    ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
    #define EG_CORE_FATEL(...)    ::Engine::Log::GetCoreLogger()->fatel(__VA_ARGS__)
    
    //Client log macros
    #define EG_TRACE(...)    ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
    #define EG_INFO(...)     ::Engine::Log::GetClientLogger()->info (__VA_ARGS__)
    #define EG_WARN(...)     ::Engine::Log::GetClientLogger()->warn (__VA_ARGS__)
    #define EG_ERROR(...)    ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
    #define EG_FATEL(...)    ::Engine::Log::GetClientLogger()->fatel(__VA_ARGS__)
    

}


