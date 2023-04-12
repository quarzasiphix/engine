#pragma once
#include <common.hpp>

namespace engine {
#define BIND_EVENT_FN(x) std::bind(&app::x, this, std::placeholders::_1)
	DEFINE_ENGINE_API;
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
		opengl* gl;
			
		//void PushLayer(Layer* layer);
		//void PushOverlay(Layer* layer);

		void onEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		bool m_running = true;
		//LayerStack m_LayerStack;
	};
	app* createApp();
}
