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

	void Entity::set_body(std::shared_ptr<Body> body)
	{
		m_body = body;
	}

	std::shared_ptr<Body> Entity::get_body()
	{
		return m_body;
	}

	Entity::Entity()
	{
		m_owner = NULL;
		m_id = 0xDEADBEEF;
	}
}