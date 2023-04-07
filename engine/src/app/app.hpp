#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API opengl;
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
		opengl* gl;
	private:
		bool m_running = true;
		
		//std::unique_ptr<window> m_window{ new window() };
		//std::unique_ptr<window> m_window;

	};
	app* createApp();
}
