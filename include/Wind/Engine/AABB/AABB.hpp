#ifndef WIND_ENGINE_AABB_AABB_HPP
#define WIND_ENGINE_AABB_AABB_HPP

#include <Wind/Maths/Vector2/Vector2.hpp>

namespace wind
{
	class AABB
	{
	public:
		Vector2f center;
		Vector2f half_size;

		bool contains(const Vector2f &point) const;
		bool intersects(const AABB &other) const;

		AABB(const Vector2f &center={0.f, 0.f}, const Vector2f &half_size={0.f, 0.f});
	};
}

#endif
