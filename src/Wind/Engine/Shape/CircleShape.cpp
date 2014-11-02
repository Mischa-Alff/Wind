#include <Wind/Engine/Shape/CircleShape.hpp>

namespace wind
{
	inline const AABB &CircleShape::get_AABB()
	{
		if(radius != m_cache_AABB.half_size.x)
		{
			m_cache_AABB.half_size.y = m_cache_AABB.half_size.x = radius;
		}
		return m_cache_AABB;
	}

	inline const AABB CircleShape::get_AABB(const Vector2f &position)
	{
		AABB a = get_AABB();
		a.center=position;
		return a;
	}

	CircleShape::CircleShape(float radius) : Shape(Circle), radius(radius) {}
}
