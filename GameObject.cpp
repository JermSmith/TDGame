#include "GameObject.h"
#include "Util\Math.h"


const sf::Vector2f& GameObject::getPosition() const { return m_position; }
void GameObject::setPosition(sf::Vector2f& position) { m_position = position; }

const sf::Vector2f& GameObject::getSize() const { return m_size; }
void GameObject::setSize(sf::Vector2f& size) { m_size = size; }

