#ifndef WIND_ENGINE_SHAPE_SHAPE_HPP
#define WIND_ENGINE_SHAPE_SHAPE_HPP

#include <Wind/Engine/AABB/AABB.hpp>

namespace wind
{
	class Shape
	{
	public:
		enum Type
		{
			None,
			Circle,
			Rectangle
		};

	protected:
		const Type m_type;

		Shape(Type type);

	public:
		const Type &type() const;

		virtual const AABB &get_AABB() = 0;
		virtual const AABB get_AABB(const Vector2f &position) = 0;

		Shape();
	};

}

#include <Wind/Engine/Shape/CircleShape.hpp>
#include <Wind/Engine/Shape/RectangleShape.hpp>

#endif
