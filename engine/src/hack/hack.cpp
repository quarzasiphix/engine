#define HACK
#include "hack.hpp"

namespace engine {
	namespace hack {
		hackor::hackor() {
			//engine::hack_log::init();
			this->m_task = new tasks();
			m_task->getList();
	
		}

		void hackor::onUpdate() {
			m_task->onUpdate();
		}

		void hackor::onEvent(event& e) {
			//eventDispatcher dispatcher(e);
			//dispatcher.dispatch<windowResizeEvent>(BIND_EVENT_FN(m_task->onUpdateRes);
		}
	}
}