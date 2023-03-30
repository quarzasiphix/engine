#pragma once
#include <common.hpp>

namespace engine {
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class ENGINE_API window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		void on_update();
		
		void SetVSync(bool enabled);
		bool IsVSync();

		window* Create(const WindowProps& props = WindowProps());
	private:
		GLFWwindow* m_window;
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
	};
}
