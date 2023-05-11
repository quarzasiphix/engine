#include "hack.hpp"

namespace engine {
	hackor::hackor() {
		this->m_task = new tasks();

		m_task->getList();
	}

	void hackor::onUpdate() {
		m_task->onUpdate();
	}
}