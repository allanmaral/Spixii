#pragma once

#include "Spixii/Events/Event.h"

namespace Spixii
{

	class SPIXII_API WindowResizeEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(WindowsResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_width(width), m_height(height) {}

		inline uint32_t GetWidth() const { return m_width; }
		inline uint32_t GetHeight() const { return m_height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

	private:
		uint32_t m_width;
		uint32_t m_height;
	};


	class SPIXII_API WindowCloseEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		WindowCloseEvent() = default;
	};

	class SPIXII_API ApplicationTickEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(ApplicationTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

			ApplicationTickEvent() = default;
	};

	class SPIXII_API ApplicationUpdateEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(ApplicationUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		ApplicationUpdateEvent() = default;
	};

	class SPIXII_API ApplicationRenderEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(ApplicationRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

			ApplicationRenderEvent() = default;
	};
}