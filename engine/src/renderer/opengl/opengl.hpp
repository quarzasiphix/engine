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
		friend gui;
		using EventCallbackFn = std::function<void(event&)>;
		struct status {
			bool success = true;
			bool GLFWInitialized = false;
			int status; 
		}; status s;
		opengl(const windowProps prop);
		opengl();
		~opengl();
		void onAttach();
		void onUpdate();
		void onDetach();
		gui* ui;
		windowProps props;
		inline void SetEventCallback(const EventCallbackFn& callback) { m_data.EventCallback = callback; }
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool vsync;
			EventCallbackFn EventCallback;
		}; WindowData m_data;
	private:
		GLFWwindow* m_window;
	};
}



//using EventCallbackFn = std::function<void(Event&)>;
		//inline void setEventCallback(const EventCallbackFn& callback) { m_data.EventCallback = callback; }

//EventCallbackFn EventCallback;