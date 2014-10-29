#include <Windtunnel/Engine/Engine/Engine.hpp>
#include <algorithm>

namespace wind
{
	void Engine::add_entity(std::shared_ptr<Entity> entity)
	{
		entity->m_id = m_id_counter++;
		entity->m_owner = this;
		m_entities.push_back(entity);
	}

	void Engine::remove_entity(std::shared_ptr<Entity> entity)
	{
		std::swap(m_entities.back(), *std::find(m_entities.begin(), m_entities.end(), entity));
		m_entities.pop_back();
	}

	void Engine::simulate(StandardDuration deltatime)
	{
		for(auto entity_itr=0; entity_itr < m_entities.size(); ++entity_itr)
		{
			auto& entity = m_entities[entity_itr];

			// Fundamental Interactions
			for(auto entity_fund_itr=entity_itr+1; entity_fund_itr < m_entities.size(); ++entity_fund_itr)
			{
				auto& entity_fund = m_entities[entity_fund_itr];
				if(!(  (entity_fund->gravity_exert && entity->gravity_affected) 
					|| (entity->gravity_exert && entity_fund->gravity_affected)))
					continue;

				auto distance_vec = entity->position - entity_fund->position;
				auto distance_pow2 = distance_vec.x*distance_vec.x + distance_vec.y*distance_vec.y;

				float force = G * (entity->mass*entity_fund->mass)/(distance_pow2);
				Vector2f direction = (entity_fund->position-entity->position) / sqrt(distance_pow2);

				if(entity_fund->gravity_exert && entity->gravity_affected)
					entity->impulse_force += direction*force;

				if(entity->gravity_exert && entity_fund->gravity_affected)
					entity_fund->impulse_force += -direction*force;
			}
		}

		for(auto& entity : m_entities)
		{
			Vector2f acceleration = (entity->force+entity->impulse_force) / entity->mass;
			entity->velocity += acceleration*deltatime.count();
			entity->position += entity->velocity*deltatime.count();
			entity->impulse_force = {0.f, 0.f};
		}
	}

	Engine::Engine() : m_id_counter{0} {}
}