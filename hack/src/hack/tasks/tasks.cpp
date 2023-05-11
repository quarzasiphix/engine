#include "tasks.hpp"

namespace engine {
	namespace hacks {
		void listproc() {
			HANDLE hProcessSnap;
			PROCESSENTRY32 pe32;

			// Take a snapshot of all processes in the system.
			hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE)
			{
				printf("Error: CreateToolhelp32Snapshot (of processes)\n");
				return;
			}

			// Set the size of the structure before using it.
			pe32.dwSize = sizeof(PROCESSENTRY32);

			// Retrieve information about the first process,
			// and exit if unsuccessful
			if (!Process32First(hProcessSnap, &pe32))
			{
				printf("Error: Process32First\n"); // Show cause of failure
				CloseHandle(hProcessSnap);          // Clean the snapshot object
				return;
			}

			// Now walk the snapshot of processes, and
			// display information about each process in turn
			do
			{
				printf("Process name: %ws\n", pe32.szExeFile);
				printf("Process ID: %d\n\n", pe32.th32ProcessID);
			} while (Process32Next(hProcessSnap, &pe32));

			CloseHandle(hProcessSnap);
		}

		void tasks::getList() {
			HANDLE hProcessSnap;
			PROCESSENTRY32 pe32;

			// Take a snapshot of all processes in the system.
			hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (hProcessSnap == INVALID_HANDLE_VALUE) {
				printf("Error: CreateToolhelp32Snapshot (of processes)\n");
				return;
			}

			// Set the size of the structure before using it.
			pe32.dwSize = sizeof(PROCESSENTRY32);

			// Retrieve information about the first process,
			// and exit if unsuccessful
			if (!Process32First(hProcessSnap, &pe32)) {
				printf("Error: Process32First\n"); // Show cause of failure
				CloseHandle(hProcessSnap);          // Clean the snapshot object
				return;
			}
			// Now walk the snapshot of processes, and
			// store information about each process in turn
			do {
				std::pair<std::wstring, DWORD> process(pe32.szExeFile, pe32.th32ProcessID);
				all_procs.push_back(process);
				m_procs.push_back(all_procs);
			} while (Process32Next(hProcessSnap, &pe32));

			CloseHandle(hProcessSnap);

			get_list = true;
		}

		tasks::tasks() {
			onAttach();
		}

		std::wstring utf8_to_utf16(const std::string& str) {
			int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
			std::wstring wstr(len, 0);
			MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, wstr.data(), len);
			return wstr;
		}

		std::string utf16_to_utf8(const std::wstring& wstr) {
			int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
			std::string str(len, 0);
			WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, str.data(), len, nullptr, nullptr);
			return str;
		}

		/*
		void columns(tasks& e, std::string name, int row, bool fav) {
			ImGui::TableNextRow();
			for (int column = 0; column < 2; column++) {
				ImGui::TableSetColumnIndex(column);
				if (column == 0) {
					ImGui::BeginTable(std::string(name + "_table").c_str(), 2);
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					if (fav == false) {
						ImGui::Text("name: %s", utf16_to_utf8(e.processes[row].first));
						if (ImGui::Button("add favorite")) {
							std::pair<std::wstring, DWORD> fav(e.processes[row].first, e.processes[row].second);
							e.favproc.push_back(fav);
						}
						ImGui::SameLine();
						if (ImGui::Button("select proc")) {
							EN_INFO("selected proc: {0} id: {1}", utf16_to_utf8(e.processes[row].first), e.processes[row].second);
						}
					}
					else if (fav == true) {
						ImGui::Text("name: %s", utf16_to_utf8(e.favproc[row].first));
						if (ImGui::Button("remove")) e.favproc.erase(e.favproc.begin() + row);
						ImGui::SameLine();
						if (ImGui::Button("select proc")) {
							EN_INFO("selected proc: {0} id: {1}", utf16_to_utf8(e.favproc[row].first), e.favproc[row].second);
						}
					}
					ImGui::EndTable();
				}
				else if (column == 1) {
					ImGui::BeginTable("id_table", 2);
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("id: ");
					ImGui::TableSetColumnIndex(1);
					if (fav == true) ImGui::Text("%d", e.processes[row].second);
					else ImGui::Text("%d", e.favproc[row].second);
					ImGui::EndTable();
				}
			}
		}

		void list(tasks& e, std::string name, bool fav) {
			static char search_query[256] = "";
			if(fav == true) ImGui::InputText("Search", search_query, IM_ARRAYSIZE(search_query));
			if (ImGui::BeginTable(std::string(name + "table").c_str(), 2, e.flags)) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text(name.c_str());
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("proc id's");
				if (fav == false)
					for (int row = 0; row < e.processes.size() + 1; row++)
						if (strstr(utf16_to_utf8(e.processes[row].first).c_str(), search_query))
							columns(e, name, row, fav);
				else for (int row = 0; row < e.favproc.size() + 1; row++)
					columns(e, name, row, fav);
				ImGui::EndTable();
			}
		}
		*/

		static bool is_adding = false;
		static bool adding_custom = false;

		void tasks::lists(const char* name, std::vector<std::pair<std::wstring, DWORD>> procs) {
			static char search_term[256] = "";
			if (ImGui::CollapsingHeader("tasks-list")) {
				if (ImGui::BeginTable(name, 2, flags)) {
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("favorite processes");
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("proc id's");
					for (int row = 0; row < procs.size(); row++) {
						ImGui::TableNextRow();
						if (strstr(utf16_to_utf8(procs[row].first).c_str(), search_term)) {
							for (int column = 0; column < 2; column++) {
								ImGui::TableSetColumnIndex(column);
								if (column == 0) {
									ImGui::BeginTable("name_table", 2);
									ImGui::TableNextRow();
									ImGui::TableSetColumnIndex(0);
									ImGui::Text("name: %s", utf16_to_utf8(procs[row].first).c_str());
									if (name == "fav") if (ImGui::Button("remove")) procs.erase(procs.begin() + row);
									else {
										if (is_adding == false) {
											if (ImGui::Button("add")) {
												selected = make_pair(procs[row].first, procs[row].second);
												is_adding = true;
											}
											ImGui::SameLine();
											if (is_selected == true && selected == procs[row]) {
												if (ImGui::Button("unselect")) {
													is_selected = false;
													selected = std::make_pair(L"", 0);
												}
											}
											else {
												if (ImGui::Button("select")) {
													selected = std::pair<std::wstring, DWORD>(procs[row].first, procs[row].second);
													is_selected = true;
													EN_INFO("selected proc {0} id: {1}", utf16_to_utf8(procs[row].first), procs[row].second);
												}
											}
										}
										else {
											if (adding_custom == true) {
												static char input[256];
												ImGui::InputText("category name: ", input, sizeof(input), NULL, NULL);
												if (ImGui::Button("add category")) {
													std::vector<std::pair<std::wstring, DWORD>> custom;
													custom.push_back(selected);
													m_procs.push_back(custom);
												}
											}
											if (ImGui::Button("favorite")) {
												fav_procs.push_back(selected);
											}
											if (ImGui::Button("custom?")) {
												adding_custom = true;
											}
										}
									}

									ImGui::EndTable();
								}
								else if (column == 1) {
									ImGui::BeginTable("id_table", 2);
									ImGui::TableNextRow();
									ImGui::TableSetColumnIndex(0);
									ImGui::Text("id: ");
									ImGui::TableSetColumnIndex(1);
									ImGui::Text("%d", procs[row].second);
									ImGui::EndTable();
								}
							}
						}
					}
					ImGui::EndTable();
				}
			}
		}

		void tasks::fav_list() {
			lists("favorite", fav_procs);
		}

		void tasks::all_list() {
			lists("all", all_procs);
		}


		void tasks::onAttach() {

		}

		char inp[256] = "";

		void tasks::onUpdate() {
			ImGui::Begin("tasks");
			ImGui::InputText("input: ", inp, sizeof(inp));
			ImGui::Text("%s", inp);

			if (get_list == false) {
				if (ImGui::Button("get list")) getList();
				ImGui::End();
				return;

			}
			if (is_selected == true) ImGui::Text("selected: %s id: %d", utf16_to_utf8(selected.first), selected.second);
			else ImGui::Text("No process selected...");
			ImGui::Text("tasks");
			fav_list();
			if (is_selected == true)
				if (ImGui::CollapsingHeader("selected")) {
					ImGui::Text("test");
				}
			all_list();
			ImGui::End();
		}

		void tasks::onDetach() {

		}
	}
}