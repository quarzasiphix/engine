#include "window.hpp"

namespace engine {
	static bool s_GLFWInitialized = false;

	window::window(const windowProps& props) {
		init(props);
	}

	window::~window() {
		shutdown();
	}

	void window::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void window::setVsync(bool enabled) {
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);
		m_data.vsync = enabled;
	}

	bool window::isVsync() const {
		return m_data.vsync;
	}

	void window::init(const windowProps& props) {
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;

		EN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			EN_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.Width, (int)props.Height, m_data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		setVsync(true);
	}
}