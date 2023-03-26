#include "window.hpp"

namespace engine {
	bool s_GLFWInitialized = false;

	window* window::Create(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		EN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			EN_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_Data);
		SetVSync(true);
	}

	void window::on_update() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void window::SetVSync(bool enabled) {	
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		m_Data.VSync = enabled;
	}
	bool window::IsVSync() {
		return m_Data.VSync;
	}
}