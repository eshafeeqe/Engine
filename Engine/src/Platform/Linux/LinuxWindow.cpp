#include "LinxWindow.h"

namespace Engine {

    static bool s_GLFWInitialized = false;
    static void GLFWErrorCallback(int error, const char* description)
    {
        EG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Ref<Window> Window::Create(const WindowProps& props)
    {
        return std::make_unique<LinuxWindow>(props);
    }

    LinuxWindow::LinuxWindow(const WindowProps& props)
    {
        Init(props);
    }

    LinuxWindow::~LinuxWindow()
    {
    }

    void LinuxWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        if(!s_GLFWInitialized)
        {
            int success = glfwInit();
            EG_CORE_ASSERT(success, "Colud not initialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }
        
        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        m_Context = std::make_unique<OpenGLContext>(m_Window);
        
        m_Context->Init();
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        //Set GLFW Callbacks 
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
            WindowData& data =  *(WindowData*)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);

            data.EventCallback(event);
        });

        
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowData& data =  *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });
        
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window,  int key, int scancode, int action, int mods)
        {
            WindowData& data =  *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {    
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {    
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
        
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
        
                }
            }

        });
        
        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
        {
            WindowData& data =  *(WindowData*)glfwGetWindowUserPointer(window);
            
            KeyTypedEvent event(codepoint);
            data.EventCallback(event);


        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data =  *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {    
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {    
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data =  *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);

        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data =  *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });
    }

    void LinuxWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void LinuxWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void LinuxWindow::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
        
        m_Data.VSync = enabled;
    }

    bool LinuxWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

    
}