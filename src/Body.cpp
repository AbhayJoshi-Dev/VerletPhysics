#include"Body.h"

Body::Body()
{

}

void Body::Update(std::vector<Entity>& entities)
{
	for (int i = 0; i < m_sticks.size(); i++)
		m_sticks[i].Update(entities);
}