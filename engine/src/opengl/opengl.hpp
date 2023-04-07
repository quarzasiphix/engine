#pragma once
#include <common.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


namespace engine {
	struct windowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		windowProps(const std::string& title = "Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};

	class ENGINE_API gui;
	class ENGINE_API opengl {
	public:
		opengl(const windowProps prop);
		bool run();
		windowProps props;
		gui* ui;
	private:
		GLFWwindow* m_window;
	};
}
