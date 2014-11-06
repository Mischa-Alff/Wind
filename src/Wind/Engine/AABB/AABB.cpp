#include <cmath>
#include <Wind/Engine/AABB/AABB.hpp>

namespace wind
{
	AABB::AABB(const Vector2f &center, const Vector2f &half_size) 
	: center{center}
	, half_size{half_size}
	{}

	inline bool AABB::contains(const Vector2f &point) const
	{
		return (std::abs(center.x-point.x) <= half_size.x) 
		    && (std::abs(center.y-point.y) <= half_size.y);
	}

	bool AABB::contains(const AABB &other) const
	{
		Vector2f constraint_half_size = half_size-other.half_size;
		return (std::abs(center.x-other.center.x) < constraint_half_size.x)
		    && (std::abs(center.y-other.center.y) < constraint_half_size.y);
	}

	bool AABB::intersects(const AABB &other) const
	{
		return (std::abs(center.x-other.center.x) <= (half_size.x+other.half_size.x))
			&& (std::abs(center.y-other.center.y) <= (half_size.y+other.half_size.y));
	}
}