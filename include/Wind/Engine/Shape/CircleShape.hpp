#ifndef WIND_ENGINE_SHAPE_CIRCLE_SHAPE_HPP
#define WIND_ENGINE_SHAPE_CIRCLE_SHAPE_HPP

#include <Wind/Engine/Shape/Shape.hpp>

namespace wind
{
	class CircleShape : public Shape
	{
	public:
		float radius;
		CircleShape(float radius=0.f);
	};
}

#endif
