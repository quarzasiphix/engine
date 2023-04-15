#pragma once
#include "events.hpp"

namespace engine {
	class ENGINE_API keyEvent : public event {
	public:
		inline int getKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		keyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class ENGINE_API keyPressedEvent : public keyEvent {
	public:
		keyPressedEvent(int keycode, int repeatCount)
			: keyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int getRepeatCount() const { return m_RepeatCount; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class ENGINE_API keyReleasedEvent : public keyEvent {
	public:
		keyReleasedEvent(int keycode)
			: keyEvent(keycode) {}

		std::string toString() const  {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}