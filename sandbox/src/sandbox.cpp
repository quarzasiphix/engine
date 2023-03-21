#include <engine.h>

class sandbox : public app {
public:
	sandbox() {

	}
	~sandbox() {

	}
};

void main() {
	sandbox* box = new sandbox();
	box->run();
	delete box;
}