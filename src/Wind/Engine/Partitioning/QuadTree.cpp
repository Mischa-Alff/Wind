#include <Wind/Engine/Partitioning/QuadTree.hpp>
#include <cmath>
#include <iostream>

namespace wind
{
	void QuadTree::clear()
	{
		m_entities.clear();
		m_entities_outside.clear();

		if(m_nodes != nullptr)
		{
			for(int i=0;i<4;++i)
			{
				m_nodes[i].clear();
			}
			delete[] m_nodes;
			m_nodes = nullptr;
		}
	}

	void QuadTree::split()
	{
		float sub_width  = m_bounds.half_size.x/2.f;
		float sub_height = m_bounds.half_size.y/2.f;

		if(m_nodes!=nullptr)
			delete[] m_nodes;

		m_nodes=new QuadTree[4];
		m_nodes[0] = QuadTree{m_depth+1, AABB{{m_bounds.center.x+sub_width, m_bounds.center.y+sub_height}, {sub_width, sub_height}}};
		m_nodes[1] = QuadTree{m_depth+1, AABB{{m_bounds.center.x-sub_width, m_bounds.center.y+sub_height}, {sub_width, sub_height}}};
		m_nodes[2] = QuadTree{m_depth+1, AABB{{m_bounds.center.x-sub_width, m_bounds.center.y-sub_height}, {sub_width, sub_height}}};
		m_nodes[3] = QuadTree{m_depth+1, AABB{{m_bounds.center.x+sub_width, m_bounds.center.y-sub_height}, {sub_width, sub_height}}};

		m_nodes[0].max_elements_before_split = m_nodes[1].max_elements_before_split = m_nodes[2].max_elements_before_split = m_nodes[3].max_elements_before_split = max_elements_before_split;
		m_nodes[0].max_depth = m_nodes[1].max_depth = m_nodes[2].max_depth = m_nodes[3].max_depth = max_depth;
		m_nodes[0].m_parent = m_nodes[1].m_parent = m_nodes[2].m_parent = m_nodes[3].m_parent = this;

		m_nodes[0].m_index=0;
		m_nodes[1].m_index=1;
		m_nodes[2].m_index=2;
		m_nodes[3].m_index=3;
	}

	int QuadTree::get_index(const AABB &rect) const
	{
		int index=-1;

		if(!m_bounds.contains(rect))
			return index;

		if(m_nodes != nullptr)
		{
			if(m_nodes[0].m_bounds.contains(rect))
				index=0;
			else if(m_nodes[1].m_bounds.contains(rect))
				index=1;
			else if(m_nodes[2].m_bounds.contains(rect))
				index=2;
			else if(m_nodes[3].m_bounds.contains(rect))
				index=3;
		}

		return index;
	}

	void QuadTree::insert(std::shared_ptr<Entity> &entity)
	{
		if(m_nodes != nullptr)
		{
			int index = get_index(entity->get_body()->get_shapes()[0]->get_AABB(entity->position));
			if(index != -1)
			{
				m_nodes[index].insert(entity);
				return;
			}
			else
			{
				if(!m_bounds.contains(entity->get_body()->get_shapes()[0]->get_AABB(entity->position)))
				{
					m_entities_outside.push_back(entity);
					return;
				}
			}
		}

		m_entities.push_back(entity);

		if(m_entities.size() > max_elements_before_split && m_depth < max_depth)
		{
			if(m_nodes == nullptr)
				split();

			int i=0;
			while(i<m_entities.size())
			{
				int index = get_index(m_entities[i]->get_body()->get_shapes()[0]->get_AABB(m_entities[i]->position));
				if(index != -1)
				{
					m_nodes[index].insert(m_entities[i]);
					m_entities.erase(m_entities.begin()+i);
				}
				else
				{
					++i;
				}
			}
		}
	}

	void QuadTree::retrieve(std::vector<std::shared_ptr<Entity> > &match, const AABB &test) const
	{
		AABB rect = test;
		rect.half_size*=2;
		int index = get_index(rect);
		if(index != -1 && m_nodes != nullptr)
		{
			m_nodes[index].retrieve(match, rect);
			match.insert(match.end(), m_entities.begin(), m_entities.end());
		}
		else if(index == -1)
		{
			if(!m_bounds.contains(test))
			{
				match.insert(match.end(), m_entities_outside.begin(), m_entities_outside.end());
				return;
			}
			get_entities_recursive(match);	
		}

		if(adjacent && index != -1)
		{
			Vector2f dist = rect.center - m_bounds.center;
			dist.x = std::abs(dist.x);
			dist.y = std::abs(dist.y);
			Vector2f dist2 = dist*2;
			Vector2f size = rect.half_size * 2;

			if(dist.x >= size.x && dist.y >= size.y)
				;
			else if(dist.x < size.x && dist.y < size.y)
			{
				if(index==0)
				{
					m_nodes[1].retrieve(match, AABB{{rect.center.x, rect.center.y-dist2.y},{rect.half_size}});
					m_nodes[2].retrieve(match, AABB{{rect.center.x-dist2.x, rect.center.y-dist2.y},{rect.half_size}});
					m_nodes[3].retrieve(match, AABB{{rect.center.x-dist2.x, rect.center.y},{rect.half_size}});
				}
				if(index==1)
				{
					m_nodes[0].retrieve(match, AABB{{rect.center.x+dist2.x, rect.center.y},{rect.half_size}});
					m_nodes[2].retrieve(match, AABB{{rect.center.x, rect.center.y-dist2.y},{rect.half_size}});
					m_nodes[3].retrieve(match, AABB{{rect.center.x+dist2.x, rect.center.y-dist2.y},{rect.half_size}});
				}
				if(index==2)
				{
					m_nodes[0].retrieve(match, AABB{{rect.center.x+dist2.x, rect.center.y+dist2.y},{rect.half_size}});
					m_nodes[1].retrieve(match, AABB{{rect.center.x, rect.center.y+dist2.y},{rect.half_size}});
					m_nodes[3].retrieve(match, AABB{{rect.center.x+dist2.x, rect.center.y},{rect.half_size}});
				}
				if(index==3)
				{
					m_nodes[0].retrieve(match, AABB{{rect.center.x, rect.center.y+dist2.y},{rect.half_size}});
					m_nodes[1].retrieve(match, AABB{{rect.center.x-dist2.x, rect.center.y+dist2.y},{rect.half_size}});
					m_nodes[2].retrieve(match, AABB{{rect.center.x-dist2.x, rect.center.y},{rect.half_size}});
				}
			}
			else if(dist.x < size.x)
			{
				if(index==0)
				{
					m_nodes[1].retrieve(match, AABB{{rect.center.x-dist2.x, rect.center.y},{rect.half_size}});
				}
				if(index==1)
				{
					m_nodes[0].retrieve(match, AABB{{rect.center.x+dist2.x, rect.center.y},{rect.half_size}});
				}
				if(index==2)
				{
					m_nodes[3].retrieve(match, AABB{{rect.center.x+dist2.x, rect.center.y},{rect.half_size}});
				}
				if(index==3)
				{
					m_nodes[2].retrieve(match, AABB{{rect.center.x-dist2.x, rect.center.y},{rect.half_size}});
				}	
			}
			else if(dist.y < size.y)
			{
				if(index==0)
				{
					m_nodes[3].retrieve(match, AABB{{rect.center.x, rect.center.y-dist2.y},{rect.half_size}});
				}
				if(index==1)
				{
					m_nodes[2].retrieve(match, AABB{{rect.center.x, rect.center.y-dist2.y},{rect.half_size}});
				}
				if(index==2)
				{
					m_nodes[1].retrieve(match, AABB{{rect.center.x, rect.center.y+dist2.y},{rect.half_size}});
				}
				if(index==3)
				{
					m_nodes[0].retrieve(match, AABB{{rect.center.x, rect.center.y+dist2.y},{rect.half_size}});
				}		
			}
		}
	}

	const QuadTree &QuadTree::node(const AABB &rect) const
	{
		int index = get_index(rect);
		if(index != -1)
			return m_nodes[index].node(rect);
		return *this;
	}

	const QuadTree *QuadTree::get_nodes() const
	{
		return m_nodes;
	}
	const AABB &QuadTree::get_bounds() const
	{
		return m_bounds;
	}
	const int QuadTree::get_depth() const
	{
		return m_depth;
	}
	const int QuadTree::get_index() const
	{
		return m_index;
	}
	const QuadTree *QuadTree::get_parent() const
	{
		return m_parent;
	}
	const std::vector<std::shared_ptr<Entity>> &QuadTree::get_entities() const
	{
		return m_entities;
	}	
	void QuadTree::get_entities_recursive(std::vector<std::shared_ptr<Entity>> &entities) const
	{
		entities.insert(entities.end(), m_entities.begin(), m_entities.end());
		if(m_nodes != nullptr)
		{
			m_nodes[0].get_entities_recursive(entities);
			m_nodes[1].get_entities_recursive(entities);
			m_nodes[2].get_entities_recursive(entities);
			m_nodes[3].get_entities_recursive(entities);
		}
	}

	QuadTree::QuadTree(int level, const AABB &bounds)
	{
		m_depth = level;
		m_bounds = bounds;
		m_nodes = nullptr;
	}

	QuadTree::QuadTree(const AABB &bounds)
	{
		m_depth = 0;
		m_bounds = bounds;
		m_nodes = nullptr;
	}

	QuadTree::~QuadTree()
	{
		clear();
		if(m_nodes != nullptr)
		{
			delete[] m_nodes;
		}
	}
}