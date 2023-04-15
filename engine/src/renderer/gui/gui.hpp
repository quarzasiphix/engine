#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API opengl;
	class ENGINE_API gui {
	public:
		friend opengl;
		gui(GLFWwindow* m_window);
		~gui();
		void onAttach();
		void onUpdate();
		void onDetach();
		GLFWwindow* m_window;
		void ui();
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		bool initialised = false;
	private:
		int display_w, display_h;
		bool init(GLFWwindow* m_window);
		//void run(GLFWwindow* m_window);
	};
}

		/*
		//void(*onRender)(gui& g);
		//void addui(void(*ui)(gui& g)); */

//void addui (void (*imgui)(gui& g));
		//void (*ui)(gui& g);