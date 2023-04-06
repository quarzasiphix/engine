#include "app.hpp"

namespace engine {
	app::app() {
		m_window = std::unique_ptr<window>(); 
		//m_window->Create();
	}

	app::~app() {
	
	}

	void app::run() {
		while (m_running) {
			m_window->onUpdate();
		}
	}
}