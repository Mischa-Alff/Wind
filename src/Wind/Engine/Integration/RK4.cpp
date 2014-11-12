#include <Wind/Engine/Integration/RK4.hpp>

namespace wind
{
	Vector2f acceleration;
	
	struct Derivative
	{
		Vector2f d_pos;
		Vector2f d_vel;
	};

	Derivative evaluate(const Entity &initial, float t, float dt, const Derivative &d)
	{
		Derivative output;
		output.d_pos = initial.velocity + d.d_vel*dt;
		output.d_vel = acceleration;
		return output;
	}

	void RK4_func(Entity &e, Engine::StandardDuration dt)
	{
		e.position += e.minimum_translation;
		acceleration = (e.force+e.impulse_force) / e.mass;
		Derivative a,b,c,d;
		a = evaluate(e, 0.f, 0.f, Derivative());
		b = evaluate(e, 0.f, dt.count()+0.5f, a);
		c = evaluate(e, 0.f, dt.count()+0.5f, b);
		d = evaluate(e, 0.f, dt.count(), c);

		Vector2f dpdt = 1.0f / 6.0f * (a.d_pos + 2.0f*(b.d_pos + c.d_pos) + d.d_pos);
		Vector2f dvdt = 1.0f / 6.0f * (a.d_vel + 2.0f*(b.d_vel + c.d_vel) + d.d_vel);

		e.position = e.position + dpdt * dt.count();
		e.velocity = e.velocity + dvdt * dt.count();
		e.minimum_translation = e.impulse_force = {0.f, 0.f};
	}
}