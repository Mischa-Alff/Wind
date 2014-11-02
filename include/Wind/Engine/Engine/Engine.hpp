#ifndef WIND_ENGINE_ENGINE_ENGINE_HPP
#define WIND_ENGINE_ENGINE_ENGINE_HPP

#include <chrono>
#include <vector>
#include <memory>
#include <Wind/Engine/Entity/Entity.hpp>

namespace wind
{
	class Engine
	{
	public:
		static constexpr float G = 6.67384e-11;
		using StandardDuration = std::chrono::duration<float>;
	private:
		unsigned int m_id_counter;
		std::vector<std::shared_ptr<Entity>> m_entities;

		void apply_gravity();
		void apply_gravity(std::shared_ptr<Entity> &a, bool both=false);
		void apply_gravity(std::shared_ptr<Entity> &a, std::vector<std::shared_ptr<Entity>>::iterator begin, bool both=false);
		void apply_gravity(std::shared_ptr<Entity> &a, std::shared_ptr<Entity> &b);

		void apply_collisions();
		void apply_collisions(std::shared_ptr<Entity> &a, std::vector<std::shared_ptr<Entity>>::iterator begin);
		void apply_collisions(std::shared_ptr<Entity> &a, std::shared_ptr<Entity> &b);

		void integrate(const StandardDuration &deltatime);
		void integrate(std::shared_ptr<Entity> &entity, const StandardDuration &deltatime);

	public:
		bool gravity=true;

		void add_entity(std::shared_ptr<Entity> entity);
		void remove_entity(std::shared_ptr<Entity> entity);

		void simulate(const StandardDuration deltatime);

		Engine();
	};
}

#endif
