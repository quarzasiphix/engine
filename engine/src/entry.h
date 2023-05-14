#pragma once
#include <engine.h>
#ifdef PLATFORM_WINDOWS
extern engine::app* engine::createApp();

int main(int argc, char** argv) {
	try {
		auto app = engine::createApp();
		app->run();
		delete app;
	}
	//catch (const engine::hack::proc::ReadMemoryException& ex) {
	//	EN_WARN("Exception caught: {0}", ex.what());
	//}
	catch (const std::exception& ex) {
		EN_WARN("Standard exception caught: {0}", ex.what());
	}
	catch (...) {
		EN_WARN("Unknown exception caught");
	}
}

#endif // PLATFORM_WINDOWS
