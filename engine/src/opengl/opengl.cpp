#include "opengl.hpp"
namespace engine {
	static bool s_GLFWInitialized = false;

	opengl::opengl(const windowProps prop) {
		this->props = prop;
		EN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Height, props.Width);

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			EN_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

		if (!m_window) {
			glfwTerminate();
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_window);
	}

	bool opengl::run() {
		while(!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

		glfwTerminate();
		return false;
	}
}