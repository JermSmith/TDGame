#include "Cursor.h"

Cursor::Cursor()
{
	
}

void Cursor::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_cursorCircle);
}

void Cursor::hide()
{
	m_cursorCircle.setRadius(0);
}

void Cursor::updatePositive(const sf::RenderWindow& window)
{
	m_cursorCircle.setRadius(32); // radius of tower hard coded into Tower.cpp (half of size().x)
	m_cursorCircle.setFillColor(sf::Color::Transparent);
	m_cursorCircle.setOutlineThickness(-2);
	m_cursorCircle.setOutlineColor(sf::Color::Cyan);
	m_cursorCircle.setPosition(sf::Vector2f((float)sf::Mouse::getPosition(window).x - m_cursorCircle.getRadius(),
		(float)sf::Mouse::getPosition(window).y - m_cursorCircle.getRadius()));
}

void Cursor::updateNegative(const sf::RenderWindow& window)
{
	m_cursorCircle.setRadius(32); // radius of tower hard coded into Tower.cpp (half of size().x)
	m_cursorCircle.setFillColor(sf::Color::Transparent);
	m_cursorCircle.setOutlineThickness(-2);
	m_cursorCircle.setOutlineColor(sf::Color::Red);
	m_cursorCircle.setPosition(sf::Vector2f((float)sf::Mouse::getPosition(window).x - m_cursorCircle.getRadius(),
		(float)sf::Mouse::getPosition(window).y - m_cursorCircle.getRadius()));
}

void Cursor::setRadius(float& radius)
{
	m_cursorCircle.setRadius(radius);
}

float Cursor::getRadius()
{
	return m_cursorCircle.getRadius();
}

