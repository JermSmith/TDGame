#include "Tower.h"
#include "Util\Random.h"

static Random<> rand2;

Tower::Tower()
{

}

Tower::Tower(sf::Vector2i position)
{
	//m_position = sf::Vector2f(position);
	//placeTower();
}

Tower::Tower(const sf::RenderWindow& window)
{
	m_size = sf::Vector2f(64, 64);
	m_position = sf::Vector2f(sf::Mouse::getPosition(window)); //position where the mouse is clicked; want this to be centre of circle

	m_circle.setRadius(m_size.x / 2);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	//origin is relative to the top left corner of the circle's surrounding "box"; in this case, set to be the centre of circle
	m_circle.setPosition(sf::Vector2f(m_position.x, m_position.y)); //origin of the circle goes to this position, which is location of click
	m_circle.setFillColor(sf::Color::Cyan);
}



void Tower::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	switch (e.type)
	{
	case sf::Event::EventType::MouseButtonReleased:
		break;

	default:
		break;
	}
}

void Tower::update()
{

}

void Tower::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_circle);

}

