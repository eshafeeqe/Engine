#include "Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine
{

     void BufferLayout::CalculateOffsetAndStride()
     {
          m_Stride = 0;
          uint32_t offset = 0;

          for(auto& element: m_Elements)
          {
               element.Offset = offset;
               offset += element.Size;
               m_Stride += element.Size; 

          }
     }

     VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
     {
          switch (Renderer::GetAPI())
          {
               case RendererAPI::None : EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
               case RendererAPI::OpenGL : return new OpenGLVertexBuffer(vertices, size);
          }
          EG_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
     }

     IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
     {
          switch (Renderer::GetAPI())
          {
               case RendererAPI::None : EG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
               case RendererAPI::OpenGL : return new OpenGLIndexBuffer(indices, count);
          }
          EG_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
        
     }

}