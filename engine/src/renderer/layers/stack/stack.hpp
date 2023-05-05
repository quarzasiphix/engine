#pragma once
#include <common.hpp>
namespace engine {
	namespace layer {
		class ENGINE_API layers;
		class ENGINE_API stack {
		public:
			stack();
			~stack();

			void pushLayer(layers* layer);
			void pushOverlay(layers* overlay);
			void popLayer(layers* layer);
			void popOverlay(layers* overlay);
				  
			std::vector<function> layers;
		private:
			std::vector<layers*> m_Layers;
			std::vector<layers*>::iterator m_LayerInsert;
		};
	}
}

