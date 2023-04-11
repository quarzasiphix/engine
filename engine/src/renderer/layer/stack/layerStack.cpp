#include "layerStack.hpp"

namespace engine {
	layerStack::layerStack() {
		m_layerInsert = m_layers.begin();
	}

	layerStack::~layerStack() {
		for (layer* layer : m_layers)
			delete layer;
	}

	void layerStack::PushLayer(layer* layer) {
		m_layerInsert = m_layers.emplace(m_layerInsert, layer);
		layer->OnAttach();
	}

	void layerStack::PushOverlay(layer* overlay) {
		m_layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void layerStack::PopLayer(layer* layer) {
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			m_layerInsert--;
			layer->OnDetach();
		}
	}

	void layerStack::PopOverlay(layer* overlay) {
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			overlay->OnDetach();
		}
	}

}