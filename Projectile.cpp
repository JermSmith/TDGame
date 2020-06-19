#include "Projectile.h"
#include "Util\Math.h"

#include <iostream>

Projectile::Projectile(sf::Vector2f startPos, sf::Vector2f endPos, float speed, int enemyStaticIndex
	, attackType towAttackType, int towAttackStrength, sf::Color towColour, float towRadius, int towNumPts)
{
	m_defineProjectilePolygon(towRadius, towNumPts);

	m_startPos = startPos;
	m_endPos = endPos;
	m_speed = speed;
	m_attackedEnemyStaticIndex = enemyStaticIndex;
	m_towerAttackType = towAttackType;
	m_towerAttackStrength = towAttackStrength;
	m_shape.setFillColor(towColour);

	m_position = m_startPos;
	m_theta = atan2f(m_endPos.y - m_startPos.y, m_endPos.x - m_startPos.x);

	m_shape.setOutlineThickness(-2.f);
	m_shape.setOutlineColor(sf::Color::Black);

	m_shape.setPosition(m_startPos);
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

	m_shape.setPosition(m_position);
}

void Projectile::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_shape);
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

const int& Projectile::getEnemyStaticIndex() const
{
	return m_attackedEnemyStaticIndex;
}

const attackType& Projectile::getTowerAttackType() const
{
	return m_towerAttackType;
}

const int& Projectile::getTowerAttackStrength() const
{
	return m_towerAttackStrength;
}

const sf::Color& Projectile::getColour() const
{
	return m_shape.getFillColor();
}

void Projectile::m_defineProjectilePolygon(float towRadius, int towNumPts)
{
	float projRadius = towRadius / 2.f; // makes the projectile half the radius of tower that shoots it
	m_shape.setPointCount(towNumPts);

	float theta;
	switch (towNumPts)
	{
	case 3: { theta = -PI / 2.; break; } // angle in radians
	case 4: { theta = -PI / 4.; break; }
	case 5: { theta = -PI / 2.; break; }
	case 6: { theta = -PI / 2.; break; }
	case 7: { theta = -PI / 2.; break; }
	case 8: { theta = -PI / 8.; break; }
	case 9: { theta = -PI / 2.; break; }
	default: { theta = 0.; break; }
	}

	for (int p = 0; p < (signed)m_shape.getPointCount(); p++)
	{
		float x = projRadius * cosf(theta);
		float y = projRadius * sinf(theta);

		m_shape.setPoint(p, sf::Vector2f(x, y));

		theta = theta + 2 * PI / m_shape.getPointCount(); // incrementing theta "getPointCount" times makes one revolution
	}
}


