#include <Wind/Engine/Shape/CircleShape.hpp>

namespace wind
{
	const AABB &CircleShape::get_AABB()
	{
		if(radius != m_cache_AABB.half_size.x)
		{
			m_cache_AABB.half_size.y = m_cache_AABB.half_size.x = radius;
			m_cache_pos_AABB = m_cache_AABB;
		}
		return m_cache_AABB;
	}

	const AABB CircleShape::get_AABB(const Vector2f &position)
	{
		if(radius != m_cache_AABB.half_size.x)
		{
			m_cache_AABB.half_size.y = m_cache_AABB.half_size.x = radius;
			m_cache_pos_AABB = m_cache_AABB;
		}
		m_cache_pos_AABB.center = position;
		return m_cache_pos_AABB;
	}

	CircleShape::CircleShape(float radius) : Shape(Circle), radius(radius) {}
}
