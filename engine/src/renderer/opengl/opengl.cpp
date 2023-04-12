#include "opengl.hpp"
namespace engine {
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
		delete ui;
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
	
	void opengl::init() {
		if (!s.GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			s.success = glfwInit();
			
			s.GLFWInitialized = true;
		}

		m_window = glfwCreateWindow(props.Height, props.Width, props.Title.c_str(), NULL, NULL);
		if (!m_window) {
			s.success = false;
			s.GLFWInitialized = false;
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_window);
		s.status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
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
	}

	void opengl::run() {
		glfwPollEvents();
		ui->run(m_window);
		glfwSwapBuffers(m_window);
	}
}