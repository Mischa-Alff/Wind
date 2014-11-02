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
	public:
		bool gravity=true;

		void add_entity(std::shared_ptr<Entity> entity);
		void remove_entity(std::shared_ptr<Entity> entity);

		void simulate(StandardDuration deltatime);

		Engine();
	};
}

#endif
