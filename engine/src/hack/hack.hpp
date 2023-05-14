#pragma once
#include <common.hpp>
//#include "log/hack_log.hpp"
#include "tasks/tasks.hpp"
#include "process/proc.hpp"

namespace engine {
	//class ENGINE_API event;
	namespace hack {
		struct ENGINE_API tasks;
		class ENGINE_API hackor {
			tasks* m_task;
		public:
			hackor();
			//void onAttach();
			void onUpdate();
			//void onDetach();
			//void onEvent(event& e);
		};
	}
}