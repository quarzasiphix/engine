#pragma once
#include <common.hpp>

namespace engine {
	struct tasks {
		std::vector<std::pair<std::wstring, DWORD>> processes;
		tasks();
		void getList();
		void list();
	};

}

