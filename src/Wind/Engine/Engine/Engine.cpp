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

	void Engine::apply_gravity()
	{
		for(auto it_a=m_entities.begin(); it_a != m_entities.end(); ++it_a)
		{
			auto &a = *it_a;
			if(!a->gravity_affected && !a->gravity_exert)
				return;
			if(!a->mass)
				return;
			for(auto it_b=it_a+1; it_b != m_entities.end(); ++it_b)
			{
				auto &b = *it_b;
				apply_gravity(a, b);
			}
		}
	}
	
	void Engine::apply_gravity(std::shared_ptr<Entity> &a, bool both)
	{
		apply_gravity(a, m_entities.begin(), both);
	}

	void Engine::apply_gravity(std::shared_ptr<Entity> &a, std::vector<std::shared_ptr<Entity>>::iterator begin, bool both)
	{
		if(!a->gravity_affected && !a->gravity_exert)
			return;
		if(!a->mass)
			return;
		for(auto it_b = begin; it_b != m_entities.end(); ++it_b)
		{
			auto &b = *it_b;
			if(both)
			{
				apply_gravity(a, b);
				continue;
			}

			if(!b->mass)
				continue;
			if(!(b->gravity_exert && a->gravity_affected))
				continue;

			auto distance_vec = a->position - b->position;
			auto distance_pow2 = distance_vec.x*distance_vec.x + distance_vec.y*distance_vec.y;

			float force = G * (a->mass*b->mass)/(distance_pow2);
			Vector2f direction = (b->position-a->position) / sqrt(distance_pow2);

			if(b->gravity_exert && a->gravity_affected)
				a->impulse_force += direction*force;
		}	
	}

	void Engine::apply_gravity(std::shared_ptr<Entity> &a, std::shared_ptr<Entity> &b)
	{
		if((!a->gravity_affected && !a->gravity_exert) || (!b->gravity_affected && !b->gravity_exert))
			return;
		if(!(b->gravity_exert && a->gravity_affected) && !(a->gravity_exert && b->gravity_affected))
			return;
		if(!a->mass || !b->mass)
			return;

		auto distance_vec = a->position - b->position;
		auto distance_pow2 = distance_vec.x*distance_vec.x + distance_vec.y*distance_vec.y;

		float force = G * (a->mass*b->mass)/(distance_pow2);
		Vector2f direction = (b->position-a->position) / sqrt(distance_pow2);

		if(b->gravity_exert && a->gravity_affected)
			a->impulse_force += direction*force;

		if(a->gravity_exert && b->gravity_affected)
			b->impulse_force += -direction*force;
	}


	void Engine::apply_collisions()
	{
		for(auto it_a=m_entities.begin(); it_a != m_entities.end(); ++it_a)
		{
			auto &a = *it_a;
			for(auto it_b=it_a+1; it_b != m_entities.end(); ++it_b)
			{
				auto &b = *it_b;
				apply_collisions(a, b);
			}
		}
	}

	void Engine::apply_collisions(std::shared_ptr<Entity> &a, std::vector<std::shared_ptr<Entity>>::iterator begin)
	{
		for(auto it_b = begin; it_b != m_entities.end(); ++it_b)
		{
			auto &b = *it_b;
			apply_collisions(a, b);
		}
	}

	void Engine::apply_collisions(std::shared_ptr<Entity> &a, std::shared_ptr<Entity> &b)
	{
		if(!(a->get_body() && b->get_body()))
			return;
		for(auto &shape_a : a->get_body()->get_shapes())
		{
			for(auto &shape_b : b->get_body()->get_shapes())
			{
				if(shape_a->get_AABB(a->position).intersects(shape_b->get_AABB(b->position)))
				{
					if(shape_a->type() == Shape::Circle)
					{
						if(shape_b->type() == Shape::Circle)
						{
							std::shared_ptr<CircleShape> ca = std::static_pointer_cast<CircleShape>(shape_a);
							std::shared_ptr<CircleShape> cb = std::static_pointer_cast<CircleShape>(shape_b);

							Vector2f tmp = a->position - b->position;
							float tmp_len_pow2 = tmp.x*tmp.x + tmp.y*tmp.y;
							float sum_rad = ca->radius+cb->radius;
							float sum_rad_pow2 = sum_rad * sum_rad;

							if(tmp_len_pow2 < sum_rad_pow2)
							{
								float tmp_len = std::sqrt(tmp_len_pow2);
								float minimum_translation_distance = sum_rad - tmp_len;
								float vel_len = std::sqrt(a->velocity.x*a->velocity.x + a->velocity.y*a->velocity.y);
								Vector2f unit_vel = a->velocity/vel_len;
								a->position -= unit_vel * minimum_translation_distance;
								tmp_len_pow2 = sum_rad_pow2;
							}

							if(tmp_len_pow2 <= sum_rad_pow2)
							{
								Vector2f old_velocity = a->velocity;
								Vector2f old_velocity_col = b->velocity;

								a->velocity = ((a->mass - b->mass)/(a->mass + b->mass)*old_velocity
								             + (2.0*b->mass)/(a->mass+b->mass)*old_velocity_col);

								b->velocity = ((b->mass - a->mass)/(a->mass + b->mass)*old_velocity_col
								             + (2.0*a->mass)/(a->mass+b->mass)*old_velocity);
							}
						}
					}
				}
			}
		}
	}


	void Engine::integrate(const StandardDuration &deltatime)
	{
		for(auto &a : m_entities)
			integrate(a, deltatime);
	}

	void Engine::integrate(std::shared_ptr<Entity> &entity, const StandardDuration &deltatime)
	{
		Vector2f acceleration = (entity->force+entity->impulse_force) / entity->mass;
		entity->velocity += acceleration*deltatime.count();
		entity->position += entity->velocity*deltatime.count();
		entity->impulse_force = {0.f, 0.f};
	}


	void Engine::simulate(const StandardDuration deltatime)
	{
		for(auto it_a = m_entities.begin(); it_a != m_entities.end(); ++it_a)
		{
			auto &a = *it_a;
			if(gravity)
				apply_gravity(a, it_a+1, true);
			integrate(a, deltatime);
			apply_collisions(a, it_a+1);
		}
	}

	Engine::Engine() : m_id_counter{0} {}
}
