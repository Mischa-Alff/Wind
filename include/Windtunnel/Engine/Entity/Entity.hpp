#include <Windtunnel/Maths/Vector2/Vector2.hpp>

namespace wind
{
	class Entity
	{
	public:
		Vector2f position{0.f, 0.f};
		Vector2f velocity{0.f, 0.f};
		Vector2f force{0.f, 0.f};
		float radius{1.f};
		float radius_pow2{1.f};
	};
}