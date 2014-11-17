#ifndef WIND_ENGINE_ENGINE_ENGINE_HPP
#define WIND_ENGINE_ENGINE_ENGINE_HPP

#include <chrono>
#include <vector>
#include <memory>
#include <Wind/Engine/Entity/Entity.hpp>
#include <Wind/Engine/Partitioning/QuadTree.hpp>

namespace wind
{
	class Engine
	{
	public:
		static constexpr float G = 6.67384e-11;
		using StandardDuration = std::chrono::duration<float>;
		using IntegrationFunction = std::function<void(Entity&, Engine::StandardDuration)>;
	private:
		unsigned int m_id_counter;
		std::vector<std::shared_ptr<Entity>> m_entities;
		std::shared_ptr<Partition> m_partition;
		IntegrationFunction m_integration_func;

		void apply_gravity();
		void apply_gravity(std::shared_ptr<Entity> &a, bool both=false);
		void apply_gravity(std::shared_ptr<Entity> &a, std::vector<std::shared_ptr<Entity>>::iterator begin, bool both=false);
		void apply_gravity(std::shared_ptr<Entity> &a, std::shared_ptr<Entity> &b);

		void apply_collisions();
		void apply_collisions(std::shared_ptr<Entity> &a, std::vector<std::shared_ptr<Entity>>::iterator begin);
		bool apply_collisions(std::shared_ptr<Entity> &a, std::shared_ptr<Entity> &b);

		void integrate(const StandardDuration &deltatime);
		void integrate(std::shared_ptr<Entity> &entity, const StandardDuration &deltatime);

	public:
		bool gravity=true;
		bool use_spatial_partitioning=false;
		bool use_minimum_translation_on_collision=true;
		bool use_partitioning_border_as_world_limit=true;

		void add_entity(std::shared_ptr<Entity> entity);
		void remove_entity(std::shared_ptr<Entity> entity);

		void set_partition_method(std::shared_ptr<Partition> tree);

		void set_integrator(IntegrationFunction &func);

		void simulate(const StandardDuration deltatime);

		Engine();
	};
}

#endif
