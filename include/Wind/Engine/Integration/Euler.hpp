#ifndef WIND_ENGINE_INTEGRATION_EULER
#define WIND_ENGINE_INTEGRATION_EULER

#include <Wind/Engine/Engine/Engine.hpp>

namespace wind
{
	void euler_func(Entity &e, Engine::StandardDuration dt);

	namespace Integrators
	{
		static Engine::IntegrationFunction Euler = euler_func;
	}
}

#endif
