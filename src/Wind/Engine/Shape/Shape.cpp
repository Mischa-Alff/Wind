#include <Wind/Engine/Shape/Shape.hpp>

namespace wind
{
	const Shape::Type &Shape::type() const
	{
		return m_type;
	}

	Shape::Shape(Type type) : m_type{type} {}
	Shape::Shape() : m_type{None} {}
}