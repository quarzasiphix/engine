#pragma once
#include <common.hpp>
#include "tasks/tasks.hpp"

namespace engine {
	//class ENGINE_API layer::layers;
	struct ENGINE_API tasks;
	class ENGINE_API event;	
	class ENGINE_API windowResizeEvent;
	class ENGINE_API opengl;
	class ENGINE_API gui {
	public:
		friend opengl;
		gui(GLFWwindow* m_window);
		~gui();
		void onAttach();
		void onUpdate();
		void onDetach();
		void onEvent(event& e);
		//void onResize(windowResizeEvent& e);
		GLFWwindow* m_window;
		void ui();
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		tasks* task;
		bool initialised = false;
		int display_w, display_h; 
		float scale_x, scale_y;
	private:
		bool init(GLFWwindow* m_window);
		//void run(GLFWwindow* m_window);
	};
}

		/*
		//void(*onRender)(gui& g);
		//void addui(void(*ui)(gui& g)); */

//void addui (void (*imgui)(gui& g));
		//void (*ui)(gui& g);