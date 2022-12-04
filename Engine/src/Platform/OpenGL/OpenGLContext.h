#pragma once

#include "egpch.h"
#include "Engine/Renderer/GraphicsContext.h"
#include "Engine/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>



namespace Engine{


    class OpenGLContext: public GraphicsContext
    {
    
    public:

      OpenGLContext(GLFWwindow* windowHandle); 

      virtual void Init() override;
      virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle; 

    };

}
