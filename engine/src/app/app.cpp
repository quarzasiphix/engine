#include "app.hpp"

namespace engine {
	app::app() {
		m_window = std::unique_ptr<Window>(Window::Create());
	}

	app::~app() {
	
	}

	void app::run() {
		while (m_running) {
			m_window->OnUpdate();
		}
	}
}