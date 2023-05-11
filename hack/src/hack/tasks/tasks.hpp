#pragma once
#include <common.hpp>
namespace engine {
	namespace hacks {
		struct ENGINE_API tasks {
			std::vector<std::vector<std::pair<std::wstring, DWORD>>> m_procs;
			std::vector<std::pair<std::wstring, DWORD>> all_procs;
			std::vector<std::pair<std::wstring, DWORD>> fav_procs;

			bool is_selected = false;
			std::pair<std::wstring, DWORD> selected;
			ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

			bool get_list = false;

			tasks();
			void getList();
			void fav_list();
			void all_list();
			void lists(const char* name, std::vector<std::pair<std::wstring, DWORD>> procs);

			void onAttach();
			void onUpdate();
			void onDetach();

			//void select();
		};
	}
}

