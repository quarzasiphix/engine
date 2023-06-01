#pragma once
#include <common.hpp>

namespace engine {
#define BIND_EVENT_FN(x) std::bind(&app::x, this, std::placeholders::_1)
	//class ENGINE_API layer::stack;
	//class ENGINE_API layer::layers;
	namespace hack {
		class ENGINE_API hackor;
	}
	class ENGINE_API event; 
	class ENGINE_API opengl; 
	class ENGINE_API windowCloseEvent;
	class ENGINE_API windowResizeEvent;
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
		opengl* gl;
		//void pushLayer(layer::layers* layer);
		//void pushOverlay(layer::layers* layer);

		void onEvent(event& e);
		void onWindowResize(windowResizeEvent& e) {

		}
		bool onWindowClose(windowCloseEvent& e);
	private:
		bool m_running = true;
		//layer::stack m_LayerStack;
	};
	app* createApp();
}
