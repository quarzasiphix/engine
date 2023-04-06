#pragma once
#include <common.hpp>
namespace engine {
	struct windowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		windowProps(const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};
	
	class ENGINE_API window {
	public:
		//window();
		~window();


		void onUpdate();

		inline unsigned int getWidth() const { return m_data.Width; }
		inline unsigned int getHeight() const { return m_data.Height; }

		void setVsync(bool enabled);
		bool isVsync() const;
		using EventCallbackFn = std::function<void(Event&)>;
		inline void setEventCallback(const EventCallbackFn& callback) { m_data.EventCallback = callback; }
		windowProps props;
		void init();
		void shutdown();
	private:

		GLFWwindow* m_window;

		struct windowData {
			std::string Title;
			unsigned int Width, Height;
			bool vsync;

			EventCallbackFn EventCallback;
		};

		windowData m_data;
	};
}
