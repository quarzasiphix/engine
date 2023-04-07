#pragma once
#include <common.hpp>

namespace engine {
#define BIND_EVENT_FN(x) std::bind(&app::x, this, std::placeholders::_1)
	class ENGINE_API opengl;
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
		opengl* gl;
		void onEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		bool m_running = true;
	};
	app* createApp();
}
