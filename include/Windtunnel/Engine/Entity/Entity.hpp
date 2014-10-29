#ifndef WINDTUNNEL_ENGINE_ENTITY_ENTITY_HPP
#define WINDTUNNEL_ENGINE_ENTITY_ENTITY_HPP

#include <Windtunnel/Maths/Vector2/Vector2.hpp>

namespace wind
{
	class Entity
	{
	private:
		friend class Engine;
		unsigned int m_id;
	public:
		Vector2f position{0.f, 0.f};
		Vector2f velocity{0.f, 0.f};
		Vector2f force{0.f, 0.f};

		unsigned int get_id();
	};
}

#endif