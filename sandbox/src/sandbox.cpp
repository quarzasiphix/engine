// includes entry point
#include <engine.h>
/*
class ExampleLayer : public engine::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override {
		EN_INFO("ExampleLayer::Update");
	}

	void OnEvent(engine::Event& event) override {
		EN_TRACE("{0}", event);
	}

};*/

class sandbox : public engine::app {
public:
	sandbox() {
		EN_CORE_WARN("intialised log!!");
		EN_INFO("hellooo");

		//PushLayer(new ExampleLayer());
	}

	~sandbox() {

	}
};

engine::app* engine::createApp() {
	return new sandbox();
}