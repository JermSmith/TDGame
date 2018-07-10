#include "Tower.h"
#include "Util\Random.h"

static Random<> rand2;

Tower::Tower()
{
	int randX = rand2.getIntInRange(50, 600);
	int randY = rand2.getIntInRange(50, 600);

	m_position = sf::Vector2f((float)randX, (float)randY);

	//sf::CircleShape c;
	m_circle.setPosition(m_position);
	m_circle.setFillColor(sf::Color::Cyan);
	m_circle.setRadius(10.);
	m_size = sf::Vector2f(20, 20);
}



void Tower::update()
{

}

void Tower::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_circle);

}