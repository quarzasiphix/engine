#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
	private:
		std::unique_ptr<class window> m_window;
		bool m_running = true;

	};
	app* createApp();
}
