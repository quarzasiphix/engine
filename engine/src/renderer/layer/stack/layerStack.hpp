#pragma once
#include <common.hpp>

namespace engine {
	class ENGINE_API layerStack {
	public:
		layerStack();
		~layerStack();

		void PushLayer(layer* layer);
		void PushOverlay(layer* overlay);
		void PopLayer(layer* layer);
		void PopOverlay(layer* overlay);

		std::vector<layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<layer*>::iterator end() { return m_layers.end(); }
	private:		
		std::vector<layer*> m_layers;
		std::vector<layer*>::iterator m_layerInsert;
	};
}

