#pragma once
#include <common.hpp>

namespace engine {
#define BIND_EVENT_FN(x) std::bind(&app::x, this, std::placeholders::_1)
	//class ENGINE_API Layer;
	class ENGINE_API Event;
	class ENGINE_API opengl;
	class ENGINE_API WindowCloseEvent;
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
