#pragma once
#include <common.hpp>

namespace engine {
	class gui {
	public:
		friend opengl;
		gui(GLFWwindow* m_window);
	private:
		int display_w, display_h;
		bool init(GLFWwindow* m_window);
		void run(GLFWwindow* m_window);
	};
}