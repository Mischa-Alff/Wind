#include <Wind/Engine/Shape/RectangleShape.hpp>

namespace wind
{
	const AABB &RectangleShape::get_AABB()
	{
		return bounding_box;
	}

	const AABB RectangleShape::get_AABB(const Vector2f &position)
	{
		m_cache_pos_AABB.half_size = bounding_box.half_size;
		m_cache_pos_AABB.center = position;
		return m_cache_pos_AABB;
	}

	RectangleShape::RectangleShape(const AABB &bounding_box) : Shape(Rectangle), bounding_box(bounding_box) {}
}
