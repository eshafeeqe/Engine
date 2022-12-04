#include "OpenGLContext.h"

struct GLFWwindow;

namespace Engine{


    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        EG_CORE_ASSERT(m_WindowHandle, "Window handle is null")
    }


    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        EG_CORE_ASSERT(status, "Failed to initialize Glad!");
        
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle); 
    }

}
