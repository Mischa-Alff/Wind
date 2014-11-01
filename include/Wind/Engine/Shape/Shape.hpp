#ifndef WIND_ENGINE_SHAPE_SHAPE_HPP
#define WIND_ENGINE_SHAPE_SHAPE_HPP

namespace wind
{
	class Shape
	{
	public:
		enum Type
		{
			None,
			Circle
		};

	protected:
		const Type m_type;

		Shape(Type type);

	public:
		const Type &type() const;

		Shape();
	};

}

#endif
