#include"Chain.h"

Chain::Chain()
{

}

void Chain::Update(std::vector<Entity>& entities)
{
	for (int i = 0; i < m_links.size(); i++)
		m_links[i].ApplyLink(entities);
}