#pragma once
#include <common.hpp>

namespace engine {
    enum class EventType {
        WindowClose,
        WindowResize,
        MouseMove,
        KeyPress
    };

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
                                virtual EventType getEventType() const override { return getStaticType(); }\
                                virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

    class Event {
    public:
        virtual ~Event() = default;
    };

    class EventDispatcher {
    public:
        explicit EventDispatcher(Event& event) : m_event(event) {}

        template<typename T, typename F>
        bool Dispatch(const F& func) {
            if (m_event.GetEventType() == T::GetStaticType()) {
                m_event.Handled = func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }


    private:
        Event& m_event;
    };



    class EventHandler {
    public:
        virtual ~EventHandler() = default;

        virtual bool OnEvent(Event& event) {
            EventDispatcher dispatcher(event);
            return dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose))
                || dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize))
                || dispatcher.Dispatch<MouseMoveEvent>(BIND_EVENT_FN(OnMouseMove))
                || dispatcher.Dispatch<KeyPressEvent>(BIND_EVENT_FN(OnKeyPress));
        }

        virtual bool OnWindowClose(WindowCloseEvent& event) { return false; }
        virtual bool OnWindowResize(WindowResizeEvent& event) { return false; }
        virtual bool OnMouseMove(MouseMoveEvent& event) { return false; }
        virtual bool OnKeyPress(KeyPressEvent& event) { return false; }
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int width, int height)
            : m_Width(width), m_Height(height) {}

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

        std::string ToString() const
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        int m_Width, m_Height;
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };


}