#pragma once
#include "egpch.h"
#include "Event.h"


namespace Engine
{
    class ENGINE_API KeyEvent : public Event
    {
        public: 
            inline int GetKeyCode() const {return m_keyCode;}

            EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        protected:
            KeyEvent(int keycode)
                :m_keyCode(keycode) {}

            int m_keyCode;

    };

    class ENGINE_API KeyPressedEvent: public KeyEvent
    {
        public:
            KeyPressedEvent(int keycode, int repeatCount)
                : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

            inline int GetRepeatCount() const { return m_RepeatCount;} 

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_keyCode << " (" << m_RepeatCount << " repeats)";
                return ss.str(); 
            }
            EVENT_CLASS_TYPE(KeyPressed)

        private:
            int m_RepeatCount; 

    };

    class ENGINE_API KeyReleasedEvent: public KeyEvent
    {
        public:
            KeyReleasedEvent(int keycode)
                : KeyEvent(keycode){}

        

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent: " << m_keyCode;
                return ss.str(); 
            }
            EVENT_CLASS_TYPE(KeyReleased)

    };
}