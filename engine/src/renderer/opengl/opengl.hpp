#pragma once
#include <common.hpp>

namespace engine {
	struct windowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		windowProps(const std::string& title = "Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	class ENGINE_API gui;
	class ENGINE_API opengl {
	public:
		opengl(const windowProps prop);
		opengl();
		~opengl();
		void init();
		bool run();

		gui* ui;
		windowProps props;
	private:
		GLFWwindow* m_window;
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		};
		WindowData m_data;
	};
}



//using EventCallbackFn = std::function<void(Event&)>;
		//inline void setEventCallback(const EventCallbackFn& callback) { m_data.EventCallback = callback; }

//EventCallbackFn EventCallback;