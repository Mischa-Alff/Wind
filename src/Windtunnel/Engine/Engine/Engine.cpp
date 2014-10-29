#include <Windtunnel/Engine/Engine/Engine.hpp>
#include <algorithm>

namespace wind
{
	void Engine::add_entity(std::shared_ptr<Entity> entity)
	{
		m_entities.push_back(entity);
	}

	void Engine::remove_entity(std::shared_ptr<Entity> entity)
	{
		std::swap(m_entities.back(), *std::find(m_entities.begin(), m_entities.end(), entity));
		m_entities.pop_back();
	}
}