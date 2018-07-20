#include "Tower.h"
#include "Util\Random.h"

static Random<> rand2;

Tower::Tower()
{
	int randX = rand2.getIntInRange(50, 500);
	int randY = rand2.getIntInRange(50, 500);

	m_position = sf::Vector2f((float)randX, (float)randY);
	m_size = sf::Vector2f(64, 64);

	m_circle.setPosition(m_position);
	m_circle.setFillColor(sf::Color::Cyan);
	m_circle.setRadius(m_size.x / 2);

}



void Tower::update()
{

}

void Tower::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_circle);

}