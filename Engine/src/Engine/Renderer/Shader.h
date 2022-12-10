#pragma once  
#include "egpch.h"
#include "Engine/Log.h"

#include <glad/glad.h>

namespace Engine
{

    class Shader
    {

    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader(); 

        void Bind() const;
        void UnBind() const;

    private:
        uint32_t m_RendererID;
    };


}