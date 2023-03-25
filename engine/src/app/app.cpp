#include <enpch.hpp>
#include "app.hpp"

namespace engine {
	app::app() {
	}

	app::~app() {
	
	}

	void app::run() {
		printf("running!!\n");
		WindowResizeEvent e(1280, 720);
		EN_TRACE(e);
		while (true);
	}
}