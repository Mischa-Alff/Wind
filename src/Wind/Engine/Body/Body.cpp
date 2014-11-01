#include <algorithm>
#include <Wind/Engine/Body/Body.hpp>

namespace wind
{
	std::vector<std::shared_ptr<Shape>> Body::get_shapes()
	{
		return m_shapes;
	}

	void Body::set_shapes(std::vector<std::shared_ptr<Shape>> shapes)
	{
		m_shapes = shapes;
	}

	void Body::add_shape(std::shared_ptr<Shape> shape)
	{
		m_shapes.push_back(shape);
	}

	void Body::remove_shape(std::shared_ptr<Shape> shape)
	{
		std::swap(m_shapes.back(), *std::find(m_shapes.begin(), m_shapes.end(), shape));
		m_shapes.pop_back();
	}

	Body::Body() {}
	Body::Body(std::vector<std::shared_ptr<Shape>> &shapes) : m_shapes(shapes) {}
}
