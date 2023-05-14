#pragma once
#include <common.hpp>
namespace engine {
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

			bool is_selected = false;
			bool get_list = false;
			std::pair<std::wstring, DWORD> selected;
			ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

			proc* m_proc;

			//template <typename T>
			void addressAccess(std::unique_ptr<baseAccessMemory>& am);

			void on_select();

			void getList();
			void selectedAccess();
			void fav_list();
			void all_list();
			void listAccess();
			void lists(const char* name, std::vector<std::pair<std::wstring, DWORD>> procs);

			void onAttach();
			void onUpdate();
			void onDetach();

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

