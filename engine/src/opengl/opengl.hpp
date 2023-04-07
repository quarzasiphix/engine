#pragma once
#include <common.hpp>


namespace engine {
	struct windowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		windowProps(const std::string& title = "Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	class ENGINE_API gui;
	class ENGINE_API opengl {
	public:
		opengl(const windowProps prop);
		bool run();
		windowProps props;
		gui* ui;
	private:
		GLFWwindow* m_window;
	};
}
