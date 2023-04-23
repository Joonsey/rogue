#pragma once
#include "entity.h"
#include <vector>

namespace EM
{
	class EntityManager
	{
		public:
			EntityManager() {};
			void render_entites()
			{
				for (auto entity : m_entities)
					entity.render();
			}
			void add_entity(entities::Entity& entity)
			{
				m_entities.push_back(entity);
			}

		private:
			std::vector<entities::Entity> m_entities;
	};

}
