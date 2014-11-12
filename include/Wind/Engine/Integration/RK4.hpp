#ifndef WIND_ENGINE_INTEGRATION_RK4
#define WIND_ENGINE_INTEGRATION_RK4

#include <Wind/Engine/Engine/Engine.hpp>

namespace wind
{
	void RK4_func(Entity &e, Engine::StandardDuration dt);

	namespace Integrators
	{
		static Engine::IntegrationFunction RK4 = RK4_func;
	}
}
#endif