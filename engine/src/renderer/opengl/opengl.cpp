#include "opengl.hpp"
namespace engine {
	static bool s_GLFWInitialized = false;

	opengl::opengl(const windowProps prop) {
		this->props = prop;
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;
		init();
	}

	opengl::opengl() {
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;
		init();
	}

	opengl::~opengl() {
		glfwTerminate();
	}
	
	void opengl::init() {
		//EN_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Height, props.Width);


		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			EN_CORE_ASSERT(success, "Could not intialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(props.Height, props.Width, props.Title.c_str(), NULL, NULL);

		if (!m_window) {
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);

		// attemp at setting up event system
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		}); 

		EN_CORE_INFO("initialised opengl, name: {0}, h: {1}, w:{2}", props.Title, props.Height, props.Width);

		ui = new gui(m_window);
		//ui->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	}

	bool opengl::run() {
		if (!glfwWindowShouldClose(m_window)) {
			ui->run(m_window);
			glfwSwapBuffers(m_window);
			glfwPollEvents();
			return true;
		}

		else return false;
	}
}