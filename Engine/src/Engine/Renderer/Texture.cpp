#include "egpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Texture.h"

namespace Engine{

    Ref<Texture2D> Texture2D::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None : EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
            case RendererAPI::API::OpenGL : return std::make_shared<OpenGLTexture2D>(filepath);
        }
        EG_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;

    }


}