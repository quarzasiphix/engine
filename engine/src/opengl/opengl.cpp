#include "opengl.hpp"
namespace engine {
	static bool s_GLFWInitialized = false;

	opengl::opengl(const windowProps prop) {
		this->props = prop;
		EN_CORE_INFO("Creating window {0} ({1}, {2})", prop.Title, prop.Height, prop.Width);

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			EN_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(prop.Height, prop.Width, prop.Title.c_str(), NULL, NULL);

		if (!m_window) {
			glfwTerminate();
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_window);
		
		EN_CORE_INFO("initialised opengl, name: {0}, h: {1}, w:{2}", prop.Title, prop.Height, prop.Width);
		
		ui = new gui(m_window);

	}

	bool opengl::run() {
		while(!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			ui->run(m_window);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

		glfwTerminate();
		return false;
	}
}