#include <Wind/Engine/Integration/Euler.hpp>

namespace wind
{
	void euler_func(Entity &e, Engine::StandardDuration dt)
	{
		e.position += e.minimum_translation;
		Vector2f acceleration = (e.force+e.impulse_force) / e.mass;
		e.velocity += acceleration*dt.count();
		e.position += e.velocity*dt.count();
		e.minimum_translation = e.impulse_force = {0.f, 0.f};
	}
}