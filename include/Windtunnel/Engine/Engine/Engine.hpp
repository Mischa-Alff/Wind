#ifndef WINDTUNNEL_ENGINE_ENGINE_ENGINE_HPP
#define WINDTUNNEL_ENGINE_ENGINE_ENGINE_HPP

#include <chrono>
#include <vector>
#include <memory>
#include <Windtunnel/Engine/Entity/Entity.hpp>

namespace wind
{
	class Engine
	{
	public:
		using StandardDuration = std::chrono::duration<float>;
	private:
		unsigned int m_id_counter;
		std::vector<std::shared_ptr<Entity>> m_entities;
	public:
		void add_entity(std::shared_ptr<Entity> entity);
		void remove_entity(std::shared_ptr<Entity> entity);

		void simulate(StandardDuration deltatime);

		Engine();
	};
}

#endif