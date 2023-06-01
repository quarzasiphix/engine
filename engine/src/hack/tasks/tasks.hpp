#pragma once
#include <common.hpp>
namespace engine {
	class ENGINE_API event;
	class ENGINE_API windowResizeEvent;
	namespace hack {
		class ENGINE_API proc;
		template <typename T>
		struct ENGINE_API accessMemory;
		class ENGINE_API baseAccessMemory;
		struct ENGINE_API tasks {
			tasks();
			std::vector<std::vector<std::pair<std::wstring, DWORD>>> m_procs;
			std::vector<std::pair<std::wstring, DWORD>> all_procs;
			std::vector<std::pair<std::wstring, DWORD>> fav_procs;
			float scale = 0;

			bool is_selected = false;
			bool get_list = false;
			std::pair<std::wstring, DWORD> selected;
			ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

			proc* m_proc;

			//template <typename T>
			void addressAccess(std::unique_ptr<baseAccessMemory>& am, int i);

			void on_select();

			void getList();

			void selectedAccess();
			void makeAccessPoint();

			void fav_list();
			void all_list();
			void listAccess();
			void lists(const char* name, std::vector<std::pair<std::wstring, DWORD>> procs);

			
			GLFWwindow* get_GLFWwindow() {
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				GLFWwindow* viewportWindow = static_cast<GLFWwindow*>(viewport->PlatformHandle);
				return viewportWindow;
			};

			void onAttach();
			void onUpdate();
			void onDetach();
	
			void onUpdateRes(engine::windowResizeEvent& e) {
				scale = e.getWidth() + e.getHeight() / 2.0f;
			}

			void onEvent(event& e);

			using EventCallbackFn = std::function<void(event&)>;
			inline void SetEventCallback(const EventCallbackFn& callback) { m_data.EventCallback = callback; }
			struct WindowData {
				std::string Title;
				unsigned int Width, Height;
				bool vsync;
				EventCallbackFn EventCallback;
			}; WindowData m_data;
			GLFWwindow* m_window;

			//void writeMemory(uint64_t address);
			//void readMemory(uint64_t address);

			union {
				int intValue;
				float floatValue;
				double doubleValue;
			};

			union {
				int readInt;
				float readFloat;
				double readDouble;
			};
		};
	}
}

