#include <Wind/Engine/Partitioning/Grid.hpp>

namespace wind
{
	void Grid::clear()
	{
		m_entities.clear();
		m_entities_outside.clear();
		m_entities_all.clear();
		m_entities.resize(static_cast<int>((m_bounds.half_size.x*2)/node_size.x));
		for(auto &v : m_entities)
			v.resize(static_cast<int>((m_bounds.half_size.y*2)/node_size.y));
	}

	void Grid::insert(std::shared_ptr<Entity> &entity)
	{
		m_entities_all.push_back(entity);
		const AABB &aabb = entity->get_body()->get_shapes()[0]->get_AABB(entity->position);
		if(!m_bounds.contains(aabb))
		{
			m_entities_outside.push_back(entity);
		}
		else
		{
			auto x = (entity->position.x-(m_bounds.center.x-m_bounds.half_size.x))/node_size.x;
			auto y = (entity->position.y-(m_bounds.center.y-m_bounds.half_size.y))/node_size.y;
			if(x < m_entities.size() && y < m_entities[x].size())
				m_entities[x][y].push_back(entity);
			else
				m_entities_outside.push_back(entity);
		}
	}

	void Grid::retrieve(std::vector<std::shared_ptr<Entity> > &match, const wind::AABB &test) const
	{
		if(m_bounds.contains(test))
		{
			auto x = (test.center.x-(m_bounds.center.x-m_bounds.half_size.x))/node_size.x;
			auto y = (test.center.y-(m_bounds.center.y-m_bounds.half_size.y))/node_size.y;
			if(x < m_entities.size() && y < m_entities[x].size())
				match.insert(match.end(), m_entities[x][y].begin(), m_entities[x][y].end());
			else
				match.insert(match.end(), m_entities_outside.begin(), m_entities_outside.end());
		}
		else
			match.insert(match.end(), m_entities_outside.begin(), m_entities_outside.end());
	}

	const AABB &Grid::get_bounds() const
	{
		return m_bounds;
	}

	const std::vector<std::shared_ptr<Entity>> &Grid::get_entities() const
	{
		return m_entities_all;
	}

	void Grid::get_entities_recursive(std::vector<std::shared_ptr<Entity>> &entities) const
	{
		entities = m_entities_all;
	}

	const std::vector<std::vector<std::vector<std::shared_ptr<Entity>>>> Grid::get_entity_vector() const
	{
		return m_entities;
	}

	Grid::Grid(const AABB &bounds, const Vector2u &node_size)
	: node_size(node_size), m_bounds(bounds)
	{
		m_entities.resize(static_cast<int>((m_bounds.half_size.x*2)/node_size.x));
		for(auto &v : m_entities)
			v.resize(static_cast<int>((m_bounds.half_size.y*2)/node_size.y));
	}
}
