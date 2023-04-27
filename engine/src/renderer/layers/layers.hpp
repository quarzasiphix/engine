#pragma once
#include <common.hpp>
#include "stack/stack.hpp"
namespace engine {
	namespace layer {
		class ENGINE_API event;	
		class ENGINE_API layers {
		public:
			layers(const std::string& name = "Layer");
			virtual ~layers();

			virtual void onAttach() {}
			virtual void onDetach() {}
			virtual void onUpdate() {}
			virtual void onEvent(event& event) {}

			inline const std::string& GetName() const { return m_DebugName; }
		protected:
			std::string m_DebugName;
		};
	}
}

