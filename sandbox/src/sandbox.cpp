// includes entry point
#include <engine.h>

class sandbox : public engine::app {
public:
	sandbox() {
		EN_CORE_WARN("intialised log!!");
		EN_INFO("hellooo");
	}

	~sandbox() {

	}
};

engine::app* engine::createApp() {
	return new sandbox();
}
