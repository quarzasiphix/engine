#pragma once
#include <common.hpp>
namespace engine {
	class ENGINE_API proc;
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

		void on_select();

		void getList();
		void fav_list();
		void all_list();
		void lists(const char* name, std::vector<std::pair<std::wstring, DWORD>> procs);

		void onAttach();
		void onUpdate();
		void onDetach();
	};
}
