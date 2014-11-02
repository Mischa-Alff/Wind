#include <Wind/Engine/Engine/Engine.hpp>
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

			if(gravity)
			{
				if(!entity->gravity_affected && !entity->gravity_exert)
					continue;
				if(!entity->mass)
					continue;
				for(auto entity_fund_itr=entity_itr+1; entity_fund_itr < m_entities.size(); ++entity_fund_itr)
				{
					auto& entity_fund = m_entities[entity_fund_itr];
					if(!entity_fund->mass)
						continue;
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

			Vector2f acceleration = (entity->force+entity->impulse_force) / entity->mass;
			entity->velocity += acceleration*deltatime.count();
			entity->position += entity->velocity*deltatime.count();
			entity->impulse_force = {0.f, 0.f};

			for(auto entity_col_itr=entity_itr+1; entity_col_itr < m_entities.size(); ++entity_col_itr)
			{
				auto& entity_col = m_entities[entity_col_itr];

				for(auto &entity_shape : entity->get_body()->get_shapes())
				{
					for(auto &entity_col_shape : entity_col->get_body()->get_shapes())
					{
						if(entity_shape->get_AABB(entity->position).intersects(entity_col_shape->get_AABB(entity_col->position)))
						{
							if(entity_shape->type() == Shape::Circle)
							{
								if(entity_col_shape->type() == Shape::Circle)
								{
									std::shared_ptr<CircleShape> c1 = std::static_pointer_cast<CircleShape>(entity_shape);
									std::shared_ptr<CircleShape> c2 = std::static_pointer_cast<CircleShape>(entity_col_shape);

									Vector2f tmp = entity->position - entity_col->position;
									float tmp_len_pow2 = tmp.x*tmp.x + tmp.y*tmp.y;
									float sum_rad = c1->radius+c2->radius;
									float sum_rad_pow2 = sum_rad * sum_rad;

									// if(tmp_len_pow2 < sum_rad_pow2)
									// {
									// 	float tmp_len = sqrt(tmp_len_pow2);
									// 	float minimum_translation_distance = sum_rad - tmp_len;
									// 	float vel_len = sqrt(entity->velocity.x*entity->velocity.x + entity->velocity.x*entity->velocity.y);
									// 	Vector2f unit_vel = entity->velocity/vel_len;
									// 	entity->position -= unit_vel * minimum_translation_distance;
									// 	tmp_len_pow2 = sum_rad_pow2;
									// }

									if(tmp_len_pow2 <= sum_rad_pow2)
									{
										Vector2f old_velocity = entity->velocity;
										Vector2f old_velocity_col = entity_col->velocity;
										entity->velocity = ((entity->mass - entity_col->mass)/(entity->mass + entity_col->mass)*old_velocity
														  + (2.0*entity_col->mass)/(entity->mass+entity_col->mass)*old_velocity_col);


										entity_col->velocity = ((entity_col->mass - entity->mass)/(entity->mass + entity_col->mass)*old_velocity_col
										                  + (2.0*entity->mass)/(entity->mass+entity_col->mass)*old_velocity);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	Engine::Engine() : m_id_counter{0} {}
}
