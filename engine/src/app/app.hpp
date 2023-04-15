#pragma once
#include <common.hpp>

namespace engine {
#define BIND_EVENT_FN(x) std::bind(&app::x, this, std::placeholders::_1)
	class ENGINE_API event; 
	class ENGINE_API opengl; 
	class ENGINE_API windowCloseEvent;
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
		opengl* gl;
			
		//void PushLayer(Layer* layer);
		//void PushOverlay(Layer* layer);

		void onEvent(event& e);
		bool onWindowClose(windowCloseEvent& e);
	private:
		bool m_running = true;
		//LayerStack m_LayerStack;
	};
	app* createApp();
}
