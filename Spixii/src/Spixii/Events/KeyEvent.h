#pragma once

#include "Spixii/Events/Event.h"

namespace Spixii
{

    class SPIXII_API KeyEvent : public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        inline uint32_t GetKeyCode() const { return m_keyCode; }

    protected:
        KeyEvent(uint32_t keyCode)
            : m_keyCode(keyCode) {}

        int m_keyCode;
    };


    class SPIXII_API KeyPressedEvent : public KeyEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyPressed)
    
    public:
        KeyPressedEvent(uint32_t keyCode, uint32_t repeatCount)
            : KeyEvent(keyCode), m_repeatCount(repeatCount) {}

        inline uint32_t GetRepeatCount() const { return m_repeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

    private:
        uint32_t m_repeatCount;
    };

    class SPIXII_API KeyReleasedEvent : public KeyEvent
    {
    public:
        EVENT_CLASS_TYPE(KeyReleased)

    public:
        KeyReleasedEvent(uint32_t keyCode)
            : KeyEvent(keyCode) {}
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }
    };
}