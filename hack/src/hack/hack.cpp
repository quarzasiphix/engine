#include "hack.hpp"

namespace engine {
	namespace hacks {
		hackor::hackor() {
			this->m_task = new tasks();
		}

		void hackor::onUpdate() {
			m_task->onUpdate();
		}
	}
}