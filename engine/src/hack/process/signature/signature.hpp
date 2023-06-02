#pragma once
#include <common.hpp>

namespace engine {
	namespace hack {
		class ENGINE_API proc;
		class ENGINE_API signature {
			proc* m_proc;
		public:
			std::vector<std::pair<std::string, uintptr_t>> m_patterns;

			signature(proc* proc) : m_proc(proc) {
			
			}

			std::vector<std::pair<std::string, uintptr_t>> get_pattern_vector() {
				return m_patterns;
			}
			
			DWORD scan(const char* sig);
		};
	}
}

