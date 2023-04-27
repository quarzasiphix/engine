#pragma once
#include <core.h>

namespace engine {
	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class eventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum eventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static eventType getStaticType() { return eventType::##type; }\
								virtual eventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class ENGINE_API event {
		friend class eventDispatcher;
	public:
		bool Handled = false;

		virtual eventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(eventCategory category) {
			return getCategoryFlags() & category;
		}
	};
		
	class eventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		eventDispatcher(event& event)
			: m_Event(event)
		{}

		template<typename T>
		bool dispatch(EventFn<T> func) {
			if (m_Event.getEventType() == T::getStaticType()) {
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const event& e) {
		return os << e.toString();
	}
}