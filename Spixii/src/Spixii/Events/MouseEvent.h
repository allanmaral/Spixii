#pragma once

#include "Spixii/Events/Event.h"
#include "Spixii/Input/InputKeys.h"

namespace Spixii
{

    class SPIXII_API MouseMovedEvent : public Event
    {
    public:
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    public:
        MouseMovedEvent(float x, float y)
            : m_mouseX(x)
            , m_mouseY(y)
        {
        }

        inline float GetX() const { return m_mouseX; }
        inline float GetY() const { return m_mouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

    private:
        float m_mouseX;
        float m_mouseY;
    };

    class SPIXII_API MouseScrolledEvent : public Event
    {
    public:
        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_xOffset(xOffset)
            , m_yOffset(yOffset)
        {
        }

        inline float GetXOffset() const { return m_xOffset; }
        inline float GetYOffset() const { return m_yOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
            return ss.str();
        }

    private:
        float m_xOffset;
        float m_yOffset;
    };

    class SPIXII_API MouseButtonEvent : public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    public:
        inline SPX_MOUSE_BUTTON GetButton() const { return m_button; }

    protected:
        MouseButtonEvent(SPX_MOUSE_BUTTON button)
            : m_button(button)
        {
        }

        SPX_MOUSE_BUTTON m_button;
    };

    class SPIXII_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        EVENT_CLASS_TYPE(MouseButtonPressed)

    public:
        MouseButtonPressedEvent(SPX_MOUSE_BUTTON button)
            : MouseButtonEvent(button)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_button;
            return ss.str();
        }
    };

    class SPIXII_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        EVENT_CLASS_TYPE(MouseButtonReleased)

    public:
        MouseButtonReleasedEvent(SPX_MOUSE_BUTTON button)
            : MouseButtonEvent(button)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_button;
            return ss.str();
        }
    };

}  // namespace Spixii