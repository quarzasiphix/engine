#pragma once
#include <common.hpp>

namespace engine {
	struct ENGINE_API tasks {
		std::vector<std::pair<std::wstring, DWORD>> processes;
		std::vector<std::pair<std::wstring, DWORD>> favproc;
		ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

		bool get_list = false;	

		tasks();
		void getList();
		void fav_list();
		void all_list();
		void list();

		//void select();
	};

}

