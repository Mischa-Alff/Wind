#ifndef WIND_ENGINE_PARTITION_PARTITION_HPP
#define WIND_ENGINE_PARTITION_PARTITION_HPP

#include <vector>
#include <memory>
#include <Wind/Engine/Entity/Entity.hpp>
#include <Wind/Engine/AABB/AABB.hpp>

namespace wind
{
	class Partition
	{
	public:
		virtual void clear() = 0;
		virtual void insert(std::shared_ptr<Entity> &entity) = 0;
		virtual void retrieve(std::vector<std::shared_ptr<Entity>> &match, const AABB &test) const = 0;
		virtual const AABB &get_bounds() const = 0;
		virtual const std::vector<std::shared_ptr<Entity>> &get_entities() const = 0;
	};
}

#endif