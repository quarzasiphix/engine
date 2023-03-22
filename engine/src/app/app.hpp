#pragma once
#include <iostream>
#include <core.h>
namespace engine {
	class ENGINE_API app {
	public:
		app();
		~app();
		void run();
	};
	app* createApp();
}
