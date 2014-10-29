#include <Windtunnel/Engine/Entity/Entity.hpp>

namespace wind
{
	unsigned int Entity::get_id()
	{
		return m_id;
	}

	const Engine *Entity::get_owner()
	{
		return m_owner;
	}

	Entity::Entity()
	{
		m_owner = 0;
		m_id = 0xDEADBEEF;
	}
}