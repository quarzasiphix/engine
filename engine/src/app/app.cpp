#include "app.hpp"

namespace engine {

	app::app() {
		engine::log::init();
		gl = new opengl(windowProps("yoo", 500, 700));
		//gl->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	app::~app() {
		delete gl;
	}

	void app::run() {
		while (m_running) {
			if(!gl->run()) m_running = false;
		}
	}
	
	/*void app::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		EN_CORE_TRACE("{0}", e);
	}

	bool app::OnWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}*/
}

/* Loop until the user closes the window 
		while (m_running) {
			m_window->onUpdate();
		}
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
/* Create a windowed mode window and its OpenGL context
		m_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
		}

		/* Make the window's context current
		glfwMakeContextCurrent(m_window);
	}
		/* Create a windowed mode window and its OpenGL context
		m_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!m_window)
		{
			glfwTerminate();
		}

		/* Make the window's context current
		glfwMakeContextCurrent(m_window);


	}
	/*
		//m_window = std::make_unique<window>();
		//_window->init();
		
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