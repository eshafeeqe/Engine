#pragma once
#include "egpch.h"

#include "Event.h"
#include "Engine/Core.h"


namespace Engine
{

    class ENGINE_API  WindowResizeEvent : public Event
    {
    
    public: 

        WindowResizeEvent(uint width, uint height)
        :    m_Width(width), m_Height(height) {}

        inline uint GetWidth()  const { return m_Width;}
        inline uint GetHeight() const { return m_Height;}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width <<" "<<m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    
    private:
        uint m_Width, m_Height; 

    };

    
    class ENGINE_API WindowCloseEvent : public Event
    {
    
    public: 

        WindowCloseEvent(){};
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowCloseEvent";
            return ss.str();
        }
        
        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    };

    class ENGINE_API   AppTickEvent : public Event
    {
    
    public: 

        AppTickEvent(){};
        
        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    };

    class ENGINE_API   AppUpdateEvent : public Event
    {
    
    public: 

        AppUpdateEvent(){};
        
        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    };

    class ENGINE_API   AppRenderEvent : public Event
    {
    
    public: 

        AppRenderEvent(){};
        
        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    };


}