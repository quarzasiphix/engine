#include "app.hpp"

namespace engine {
	static bool s_GLFWInitialized = false;

	app::app() {
		engine::log::init();
		m_window = std::make_unique<window>();
		m_window->init();
	}
	/*
		
		EN_CORE_INFO("Creating window {0} ({1}, {2})", "title", 300, 200);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			EN_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		/* Create a windowed mode window and its OpenGL context 
		m_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
		}

		/* Make the window's context current 
		glfwMakeContextCurrent(m_window);
		*/

	app::~app() {
		
	}

	void app::run() {
		while (m_running) {
			m_window->onUpdate();
		}
	}
		/* Loop until the user closes the window 
		while (!glfwWindowShouldClose(m_window))
		{
			/* Render here 
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers 
			glfwSwapBuffers(m_window);

			/* Poll for and process events 
			glfwPollEvents();
		}

		glfwTerminate();

		*/
}