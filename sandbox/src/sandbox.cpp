#include <engine.h>

class sandbox : public app {
public:
	sandbox() {

	}
	~sandbox() {

	}
};

int main() {
	sandbox* box = new sandbox();
	box->run();
	delete box;
}