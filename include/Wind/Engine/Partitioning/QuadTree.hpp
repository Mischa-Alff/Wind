#ifndef WIND_ENGINE_PARTITIONING_QUADTREE_HPP
#define WIND_ENGINE_PARTITIONING_QUADTREE_HPP

#include <vector>
#include <memory>
#include <Wind/Engine/Entity/Entity.hpp>
#include <Wind/Engine/AABB/AABB.hpp>

namespace wind
{
	class QuadTree
	{
		public:
			unsigned int max_elements_before_split;
			unsigned int max_depth;
		private:
			int m_depth;
			std::vector<std::shared_ptr<Entity>> m_entities;
			AABB m_bounds;
			Vector2f m_tolerances;
			QuadTree *m_nodes;
			QuadTree *m_parent;
			int m_index;

			void split();
			int get_index(const AABB &rect) const;

		public:
			void clear();
			void insert(std::shared_ptr<Entity> &rect);
			const QuadTree &node(const AABB &entity) const;
			void retrieve(std::vector<std::shared_ptr<Entity>> &match, const AABB &test, bool adjacent=false) const;
			const QuadTree *get_nodes() const;
			const AABB &get_bounds() const;
			const int get_depth() const;
			const int get_index() const;
			const QuadTree *get_parent() const;
			const std::vector<std::shared_ptr<Entity>> &get_entities() const;
			void get_entities_recursive(std::vector<std::shared_ptr<Entity>> &entities) const;

			QuadTree(const AABB &bounds={{0,0},{0,0}});
			QuadTree(int level, const AABB &bounds);
			~QuadTree();
	};
}
#endif