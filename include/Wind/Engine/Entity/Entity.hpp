#ifndef WIND_ENGINE_ENTITY_ENTITY_HPP
#define WIND_ENGINE_ENTITY_ENTITY_HPP

#include <cstdint>
#include <memory>
#include <Wind/Engine/Body/Body.hpp>
#include <Wind/Maths/Vector2.hpp>

namespace wind
{
	class Engine;
	class Entity
	{
	private:
		friend class Engine;
		unsigned int m_id;
		const Engine *m_owner;
		std::shared_ptr<Body> m_body;

	public:
		Vector2f position{0.f, 0.f};
		Vector2f velocity{0.f, 0.f};
		Vector2f force{0.f, 0.f};
		Vector2f impulse_force{0.f, 0.f};
		float mass{1.f};

		bool gravity_exert{false};
		bool gravity_affected{false};

		unsigned int get_id();
		const Engine *get_owner();

		void set_body(std::shared_ptr<Body> body);
		std::shared_ptr<Body> get_body();

		Entity();
	};
}

#endif
