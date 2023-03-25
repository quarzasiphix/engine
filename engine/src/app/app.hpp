#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
	};
	app* createApp();
}
