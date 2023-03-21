#pragma once
#include <engine.h>
#ifdef PLATFORM_WINDOWS
extern engine::app* engine::createApp();

int main(int argc, char** argv) {
	auto app = engine::createApp();
	app->run();
	delete app;
}

#endif // PLATFORM_WINDOWS
