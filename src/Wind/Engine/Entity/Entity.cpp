#include <Wind/Engine/Entity/Entity.hpp>

#include <cstddef>

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
		m_owner = NULL;
		m_id = 0xDEADBEEF;
	}
}