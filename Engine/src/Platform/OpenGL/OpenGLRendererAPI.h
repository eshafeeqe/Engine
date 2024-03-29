#pragma once

#include "Engine/Renderer/RendererAPI.h"
#include "Engine/Renderer/VertexArray.h"

namespace Engine{

    class OpenGLRendererAPI: public RendererAPI
    {
    public:
        OpenGLRendererAPI(){};
        virtual ~OpenGLRendererAPI(){};

        virtual void Init() override;
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;
        virtual void DrawIndexed(const Ref<VertexArray> vertexArray ) override; 

    };
}