#include "tasks.hpp"

namespace engine {

	std::string WideStringToString(std::wstring& wideStr) {
		int size = WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string utf8Str(size, 0);
		WideCharToMultiByte(CP_UTF8, 0, wideStr.c_str(), -1, &utf8Str[0], size, nullptr, nullptr);
		return utf8Str;
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

	bool attached = false;
	
	static bool is_adding = false;
	static bool adding_custom = false;
	static char search_term[256] = "";
	static char all_search[256] = "";
	static char fav_search[256] = "";
	
	void tasks::lists(const char* name,  std::vector<std::pair<std::wstring, DWORD>> procs) {
		if (ImGui::CollapsingHeader(name)) {
			if (name == "all") {
				//ImGui::SetKeyboardFocusHere();
				//if(ImGui
				ImGui::InputText("input: ", search_term, sizeof(search_term));
			}
			if (ImGui::BeginTable(name, 2, flags)) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("favorite processes");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text("proc id's");
				for (int row = 0; row < procs.size(); row++) {
					if (strstr(utf16_to_utf8(procs[row].first).c_str(), search_term)) {
						ImGui::TableNextRow();

						for (int column = 0; column < 2; column++) {
							ImGui::TableSetColumnIndex(column);

							if (column == 0) {
								ImGui::BeginTable("name_table", 2);
								ImGui::TableNextRow();
								ImGui::TableSetColumnIndex(0);
								ImGui::Text("name: %s", utf16_to_utf8(procs[row].first).c_str());

								//if (name == "all") {
								const std::wstring& valueToCheck = procs[row].first;
								bool isValueInFavProc = false;
								int foundIndex = -1;

								for (int i = 0; i < fav_procs.size(); ++i) {
									if (fav_procs[i].first == valueToCheck) {
										isValueInFavProc = true;
										foundIndex = i;
										break;
									}
								}

								if (isValueInFavProc == true) {
									// The value exists in fav_procs vector
									// You can access the element using fav_procs[foundIndex]

									if (ImGui::Button("remove"))
										fav_procs.erase(fav_procs.begin() + foundIndex);
								}
								else {
									// The value doesn't exist in fav_procs vector
									if (ImGui::Button("add favorite")) {
										selected = std::make_pair(procs[row].first, procs[row].second);
										fav_procs.push_back(selected);
									}
								}

								ImGui::SameLine();
								if (is_selected && selected == procs[row]) {
									if (ImGui::Button("unattach")) {
										is_selected = false;
										selected = std::make_pair(L"", 0);
										attached = false;
										delete m_proc;
									}
								}
								else {
									if (ImGui::Button("attach")) {
										selected = std::make_pair(procs[row].first, procs[row].second);
										is_selected = true;
										EN_INFO("selected proc {0} id: {1}", utf16_to_utf8(procs[row].first), procs[row].second);
										on_select();
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


	void tasks::on_select() {
		EN_INFO("Attaching proccess : pid {0} :", selected.second);
		m_proc = new proc(selected.first);
		if (m_proc == NULL) {
			EN_WARN("Failed attaching to process");
			return;
		}
		else {
			attached = true;
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

	enum class DataType {
		Int,
		Float,
		Double
	};

	int intValue = 0;
	float floatValue = 0.0f;
	double doubleValue = 0.0;
	DataType selectedType = DataType::Int;

	static uint64_t address = 0;

	template <typename T>
	T read;
	bool is_written = false;

	void tasks::readMemory() {
		try {
			switch (selectedType) {
			case DataType::Int:
				readInt = m_proc->readProcMem<int>(reinterpret_cast<LPVOID>(address));
				break;
			case DataType::Float:
				readFloat = m_proc->readProcMem<float>(reinterpret_cast<LPVOID>(address));
				break;
			case DataType::Double:
				readDouble = m_proc->readProcMem<double>(reinterpret_cast<LPVOID>(address));
				break;
			}
			if (!m_proc->read_success)  EN_INFO("Succesfully read memory");
			else EN_WARN("Failed reading memory");
		}
		catch (const engine::proc::ReadMemoryException& ex) {
			EN_WARN("Exception caught: {0}", ex.what());
		}
		catch (const std::exception& ex) {
			EN_WARN("Standard exception caught: {0}", ex.what());
		}
		catch (...) {
			EN_WARN("Unknown exception caught");
		}
	}

	void tasks::writeMemory() {
		switch (selectedType) {
		case DataType::Int:
			if (m_proc->writeProcMem(reinterpret_cast<LPVOID>(address), intValue)) is_written = true;
			break;
		case DataType::Float:
			if (m_proc->writeProcMem(reinterpret_cast<LPVOID>(address), floatValue)) is_written = true;
			break;
		case DataType::Double:
			if (m_proc->writeProcMem(reinterpret_cast<LPVOID>(address), doubleValue)) is_written = true;
			break;
		}
		if(!is_written) EN_INFO("Succesfully written memory : Address {0} : ", address);
	}

	bool mem_acc = true;

	void tasks::selectedAccess() {
		ImGui::Text("selected: %s id: %d", utf16_to_utf8(selected.first), selected.second);
		ImGui::Text("Selected Type: %d", static_cast<int>(selectedType));
		if (ImGui::CollapsingHeader("Access memory", mem_acc)) {

			ImGui::Indent();

			ImGui::Spacing();
			ImGui::Spacing();


			ImGui::Text("Access specific memory address");
			const char* items[] = { "Int", "Float", "Double" };
			int itemIndex = static_cast<int>(selectedType);
			if (ImGui::Combo("Type", &itemIndex, items, IM_ARRAYSIZE(items))) {
				selectedType = static_cast<DataType>(itemIndex);
			}

			switch (selectedType) {
			case DataType::Int:
				ImGui::InputInt("write value", &intValue);
				break;
			case DataType::Float:
				ImGui::InputFloat("write value", &floatValue);
				break;
			case DataType::Double:
				ImGui::InputDouble("write value", &doubleValue);
				break;
			}

			ImGui::InputScalar("Address", ImGuiDataType_U64, &address, NULL, NULL, "%016llX", ImGuiInputTextFlags_CharsHexadecimal);


			ImGui::Spacing();

			try {
				if (address != 0) {
					if (ImGui::Button("Write"))
						writeMemory();
					if (ImGui::Button("Read"))
						readMemory();

					if (m_proc->read_success == true) {
						switch (selectedType) {
						case DataType::Int:
							ImGui::Text("Value: %d", readInt);
							break;
						case DataType::Float:
							ImGui::Text("Value: %f", readFloat);
							break;
						case DataType::Double:
							ImGui::Text("Value: %f", readDouble);
							break;
						}
					}
				}
			}
			catch (const engine::proc::ReadMemoryException& ex) {
				EN_WARN("Exception caught: {0}", ex.what());
			}
			catch (const std::exception& ex) {
				EN_WARN("Standard exception caught: {0}", ex.what());
			}
			catch (...) {
				EN_WARN("Unknown exception caught");
			}
			ImGui::Unindent();
		}
	}

	void tasks::listAccess() {
		ImGui::Text("tasks");
		ImGui::BeginChild("##scrollable_column", ImVec2(0, ImGui::GetWindowHeight()), true);
		{
			fav_list();
			all_list();
		}
		ImGui::EndChild();
	}

	static int tab;
	ImVec2 button = ImVec2(100, 50);

	uintptr_t stackPointer = 0;  // Define a variable to store the RSP value

	bool open_task = true;

	void tasks::onUpdate() {
		ImGui::Begin("tasks", &open_task, ImGuiWindowFlags_None);

		if(ImGui::Button("get list")) getList();
		ImGui::Columns(3, "tabs", false);
		ImGui::SetColumnWidth(0, 110); {
			if (ImGui::Button("tasks", button)) tab = 1;
			if (attached == true && ImGui::Button("attached", button)) tab = 2;
		}

		ImGui::SetColumnWidth(1, 600);
		ImGui::NextColumn();

		switch (tab) {
		case 1:
			listAccess();
			break;
		case 2:
			selectedAccess();
			break;
		default:
			listAccess();
			break;
		}
		
		ImGui::NextColumn();

		ImGui::Text("Attached window");
		if (is_selected == false) ImGui::Text("No process selected...");
		try {
			if (attached == true) {
				if(m_proc->is_access = 2)
					ImGui::Text("Not enough priviledges to attach.");

				if (m_proc->attached == true) {
					ImGui::Text("attached: %s id: %d", utf16_to_utf8(selected.first), selected.second);
					//int mainThreadId = m_proc->m_thread->get_mainthreadid();
					//ImGui::Text("main thread id: %i", mainThreadId);
					//m_proc->get_address(start, end);
					uintptr_t start = m_proc->get_startAddress();
					uintptr_t end = m_proc->get_endAddress();
					ImGui::Text("start address: %#lx \nend address: %#lx", start, end);

					// Assign the RSP register value to the variable
					ImGui::Text("Rsp pointer: %#lx", m_proc->get_rsp());
				}
			}
		}
		catch (...) {
			EN_WARN("Failed getting rsp");
		}

		//if (is_selected == true) selectedAccess();

		ImGui::End();
	}
}