#include "tasks.hpp"

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

namespace engine {
	void tasks::getList() {
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
		// store information about each process in turn
		do
		{
			std::pair<std::wstring, DWORD> process(pe32.szExeFile, pe32.th32ProcessID);
			processes.push_back(process);
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);
	}

	tasks::tasks() {
		EN_INFO("getting list of tasks");
		getList();
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

	void tasks::list() {
		ImGui::Begin("tasks");
		static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;

		if (ImGui::BeginTable("table1", 2, flags)) {

			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("processes");
			ImGui::TableSetColumnIndex(1);
			ImGui::Text("proc id's");

			for (int row = 0; row < processes.size() + 1; row++) {
				ImGui::TableNextRow();
				for (int column = 0; column < 2; column++) {
					ImGui::TableSetColumnIndex(column);
					if (column == 0) {
						ImGui::BeginTable("nested_table1", 2);
						ImGui::TableNextRow();
						ImGui::TableSetColumnIndex(0);
						ImGui::Text("%s", utf16_to_utf8(processes[row].first).c_str());
						ImGui::EndTable();
					}
					else if (column == 1) {
						ImGui::BeginTable("nested_table2", 2);
						ImGui::TableNextRow();
						ImGui::TableSetColumnIndex(0);
						ImGui::Text("id:");
						ImGui::TableSetColumnIndex(1);
						ImGui::Text("%d", processes[row].second);
						ImGui::EndTable();
					}
				}
			}
			ImGui::EndTable();
		}
		/*
		int i = 0;
		for (const auto& process : processes) {
			std::string name = "name: " + utf16_to_utf8(process.first) + std::to_string(i);
			ImGui::Text(name.c_str());
			ImGui::Text("id: %d", process.second);
			i++;
		}
		*/
		ImGui::End();
	}
}