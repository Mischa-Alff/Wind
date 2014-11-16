#ifndef WIND_ENGINE_SHAPE_RECTANGLE_SHAPE_HPP
#define WIND_ENGINE_SHAPE_RECTANGLE_SHAPE_HPP

#include <Wind/Engine/Shape/Shape.hpp>

namespace wind
{
	class RectangleShape : public Shape
	{
	private:
		AABB m_cache_pos_AABB;
	public:
		AABB bounding_box;

		const AABB &get_AABB();
		const AABB get_AABB(const Vector2f &position);

		RectangleShape(const AABB &bounding_box={{0,0},{0,0}});
	};
}

#endif
