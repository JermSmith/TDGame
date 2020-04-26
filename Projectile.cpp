#include "Projectile.h"

#include <iostream>

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f endPos, float speed, sf::Color colour)
{
	m_startPos = startPos;
	m_endPos = endPos;
	
	m_position = m_startPos;
	
	m_circle.setFillColor(colour);
	m_circle.setOutlineThickness(-2.f);
	m_circle.setOutlineColor(sf::Color::Black);
	//m_circle.setFillColor(sf::Color::White);
	m_circle.setRadius(16.f);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setPosition(m_startPos);

	m_speed = speed;
	m_theta = atan2f(m_endPos.y - m_startPos.y, m_endPos.x - m_startPos.x);
}


void Projectile::update()
{
	if (m_position.x * cosf(m_theta) > m_endPos.x * cosf(m_theta) &&
		m_position.y * sinf(m_theta) > m_endPos.y * sinf(m_theta))
	{
		m_position = m_endPos; // have reached the target
	}
	else
	{
		m_position.x = m_position.x + m_speed * cosf(m_theta);
		m_position.y = m_position.y + m_speed * sinf(m_theta);
	}

	m_circle.setPosition(m_position);
}

void Projectile::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_circle);
}

const sf::Vector2f& Projectile::getPosition() const
{
	return m_position;
}

void Projectile::setPosition(sf::Vector2f& position)
{
	m_position = position;
}

const sf::Vector2f& Projectile::getEndPos() const
{
	return m_endPos;
}