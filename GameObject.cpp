#include "GameObject.h"


const sf::Vector2f& GameObject::getPosition() const { return m_position; }

const sf::Vector2f& GameObject::getSize() const { return m_size; }
		

void GameObject::setPosition(sf::Vector2f& position) { m_position = position; }

void GameObject::setSize(sf::Vector2f& size) { m_size = size; }


bool GameObject::interferesWithPath(Path& path, float tol)
{
	for (unsigned int v = 1; v < path.getVertices().size(); v++)
	{

	}

	return false;
}