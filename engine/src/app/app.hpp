#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
		
		window* m_window;
	private:
		//std::unique_ptr<window> m_window;
		bool m_running = true;

	};
	app* createApp();
}
