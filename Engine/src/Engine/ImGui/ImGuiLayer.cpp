#include "ImGuiLayer.h"
namespace Engine
{
    
    ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
    {
        
    }

    ImGuiLayer::~ImGuiLayer() {
        
    }

    void ImGuiLayer::OnUpdate() {
        
        ImGuiIO& io = ImGui::GetIO();
        Application* app = Application::Get();
        io.DisplaySize = ImVec2(app->GetWindow()->GetWidth(), app->GetWindow()->GetHeight() );
        
        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0 ? (time - m_Time): (1.0f/60.0f);
        m_Time = time;
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        
        io.BackendFlags |=  ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |=  ImGuiBackendFlags_HasSetMousePos;

        //Temperory
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
        
        ImGui_ImplOpenGL3_Init("#version 410");
    }


    void ImGuiLayer::OnDetach()
    {
        
    }

    void ImGuiLayer::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(EG_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(EG_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(EG_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(EG_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(EG_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(EG_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(EG_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
        dispatcher.Dispatch<KeyTypedEvent>(EG_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        
    }


    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {

        ImGuiIO& IO = ImGui::GetIO();
        IO.MouseDown[e.GetMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.MouseDown[e.GetMouseButton()] = false;
        return false;
         
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.MousePos =  ImVec2(e.GetX(), e.GetY());
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.MouseWheelH +=  e.GetXOffset();
        IO.MouseWheel  +=  e.GetYOffset();

        return false;

    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.KeysDown[e.GetKeyCode()] = true;

        IO.KeyCtrl =  IO.KeysDown[GLFW_KEY_LEFT_CONTROL] || IO.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        IO.KeyAlt =  IO.KeysDown[GLFW_KEY_LEFT_ALT] || IO.KeysDown[GLFW_KEY_RIGHT_ALT];
        IO.KeyShift =  IO.KeysDown[GLFW_KEY_LEFT_SHIFT] || IO.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        IO.KeySuper =  IO.KeysDown[GLFW_KEY_LEFT_SUPER] || IO.KeysDown[GLFW_KEY_RIGHT_SUPER];
        

        return false;

    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.KeysDown[e.GetKeyCode()] = false;

        return false;

    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& IO = ImGui::GetIO();
        
        IO.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        IO.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0,  e.GetWidth(), e.GetHeight());

        return false;

    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& IO = ImGui::GetIO();
        IO.AddInputCharacter(e.GetKeyCode());

        return false;
    }


}