#pragma once
#include <common.hpp>

namespace engine {
	struct ENGINE_API tasks {
		std::vector<std::pair<std::wstring, DWORD>> processes, favproc;
		bool is_selected = false;
		std::pair<std::wstring, DWORD> selected;
		ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

		bool get_list = false;	

		tasks();
		void getList();
		void fav_list();
		void all_list();
		void lists();

		//void select();
	};

}

