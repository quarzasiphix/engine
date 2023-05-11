#include "opengl.hpp"
namespace engine {
	opengl::opengl(const windowProps prop) {
		this->props = prop;
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;
		onAttach();
	}

	opengl::opengl() {
		m_data.Title = props.Title;
		m_data.Width = props.Width;
		m_data.Height = props.Height;
		onAttach();
	}

	opengl::~opengl() {
		onDetach();
	}
	
	void opengl::onAttach() {
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
		{
			glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
					
				windowResizeEvent event(width, height);
				data.EventCallback(event);
				});
			glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				windowCloseEvent event;
				data.EventCallback(event);
				});
			glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
				case GLFW_PRESS: {
					keyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					keyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					keyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}}
			});
			glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
				case GLFW_PRESS: {
					mouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					mouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});
			glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				mouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
			glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				mouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
		}

		EN_CORE_INFO("initialised opengl, name: {0}, h: {1}, w:{2}", props.Title, props.Height, props.Width);

		ui = new gui(m_window);
	}

	void opengl::onUpdate() {
		if (ui->initialised == true)
			ui->onUpdate();
		
		glfwPollEvents();
		
		glfwGetFramebufferSize(ui->m_window, &ui->display_w, &ui->display_h);
		glfwGetWindowContentScale(ui->m_window, &ui->scale_x, &ui->scale_y);
		glViewport(0, 0, static_cast<int>(ui->display_w * ui->scale_x), static_cast<int>(ui->display_h * ui->scale_y));

		glClearColor(ui->clear_color.x * ui->clear_color.w, ui->clear_color.y * ui->clear_color.w, ui->clear_color.z * ui->clear_color.w, ui->clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT); // clear color buffer with the specified color
		
		glfwSwapBuffers(m_window);
	}

	void opengl::onDetach() {
		delete ui;
		glfwDestroyWindow(m_window);
		glfwTerminate();
	} 
}