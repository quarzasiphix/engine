#include <engine.h>

class sandbox : public engine::app {
public:
	sandbox() {

	}
	~sandbox() {

	}
};

engine::app* engine::createApp() {
	return new sandbox();
}
