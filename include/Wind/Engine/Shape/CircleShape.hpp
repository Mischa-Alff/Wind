#ifndef WIND_ENGINE_SHAPE_CIRCLE_SHAPE_HPP
#define WIND_ENGINE_SHAPE_CIRCLE_SHAPE_HPP

#include <Wind/Engine/Shape/Shape.hpp>

namespace wind
{
	class CircleShape : public Shape
	{
	private:
		AABB m_cache_AABB;
	public:
		float radius;

		const AABB &get_AABB();
		const AABB get_AABB(const Vector2f &position);

		CircleShape(float radius=0.f);
	};
}

#endif
