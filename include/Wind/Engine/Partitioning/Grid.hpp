#ifndef WIND_ENGINE_PARTITIONING_GRID_HPP
#define WIND_ENGINE_PARTITIONING_GRID_HPP

#include <vector>
#include <memory>
#include <Wind/Engine/Entity/Entity.hpp>
#include <Wind/Engine/AABB/AABB.hpp>
#include <Wind/Engine/Partitioning/Partitioning.hpp>

namespace wind
{
	class Grid : public Partition
	{
		public:
			Vector2f node_size;
			bool adjacent=false;
		private:
			std::vector<std::vector<std::vector<std::shared_ptr<Entity>>>> m_entities;
			std::vector<std::shared_ptr<Entity>> m_entities_outside;
			std::vector<std::shared_ptr<Entity>> m_entities_all;
			AABB m_bounds;

		public:
			void clear();
			void insert(std::shared_ptr<Entity> &entity);
			void retrieve(std::vector<std::shared_ptr<Entity>> &match, const AABB &test) const;
			const AABB &get_bounds() const;
			const std::vector<std::shared_ptr<Entity>> &get_entities() const;
			void get_entities_recursive(std::vector<std::shared_ptr<Entity>> &entities) const;
			const std::vector<std::vector<std::vector<std::shared_ptr<Entity>>>> get_entity_vector() const;

			Grid(const AABB &bounds={{0,0},{0,0}}, const Vector2f &node_size={1,1});
	};
}
#endif
