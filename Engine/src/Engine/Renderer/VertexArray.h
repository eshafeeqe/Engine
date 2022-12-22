#pragma once 

#include "egpch.h"
#include "Engine/Log.h"
#include "Engine/Renderer/Buffer.h"

namespace Engine {

    class VertexArray
    {
    public:
        
        VertexArray() {};
        virtual ~VertexArray() {};
        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void AddVertexBuffer (const Ref<VertexBuffer> vertexBuffer) = 0;
        virtual void SetIndexBuffer  (const Ref<IndexBuffer> indexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        static VertexArray* Create(); 
    };
    

}