#pragma once
#include <hack.h>
#include "tasks/tasks.hpp"

namespace engine {
	namespace hack {
		struct ENGINE_API tasks;
		class ENGINE_API hack {
			tasks* m_task;

		public:
			hack();
		};
	}
}