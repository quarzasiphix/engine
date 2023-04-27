#pragma once
#include <common.hpp>

namespace engine {
	struct ENGINE_API tasks {
		std::vector<std::pair<std::wstring, DWORD>> processes;
		std::vector<std::pair<std::wstring, DWORD>> favproc;

		tasks();
		void getList();
		void list();

		//void select();
	};

}

