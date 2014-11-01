#ifndef WIND_ENGINE_BODY_BODY_HPP
#define WIND_ENGINE_BODY_BODY_HPP

#include <memory>
#include <vector>
#include <Wind/Engine/Shape/Shape.hpp>

namespace wind
{
	class Body
	{
	private:
		std::vector<std::shared_ptr<Shape>> m_shapes;

	public:

		std::vector<std::shared_ptr<Shape>> get_shapes();
		void set_shapes(std::vector<std::shared_ptr<Shape>> shapes);

		void add_shape(std::shared_ptr<Shape> shape);
		void remove_shape(std::shared_ptr<Shape> shape);

		Body();
		Body(std::vector<std::shared_ptr<Shape>> &shapes);
	};
}
#endif