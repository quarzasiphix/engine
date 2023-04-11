#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API layer {
	public:
		layer(const std::string& name = "Layer");
		virtual ~layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_debugName; }
	protected:
		std::string m_debugName;
	};
}
