#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Util\AttackTypes.h"

class Projectile
{
public:

	Projectile(sf::Vector2f startPos, sf::Vector2f endPos, float speed, int enemyStaticIndex
		, attackType towAttackType, int towAttackStrength, sf::Color towColour, float towRadius, int towNumPts);

	void update();
	void render(sf::RenderTarget& renderer);

	const sf::Vector2f& getPosition() const;
	void setPosition(sf::Vector2f&);

	const sf::Vector2f& getEndPos() const;

	const int& getEnemyStaticIndex() const;
	const attackType& getTowerAttackType() const;
	const int& getTowerAttackStrength() const;
	const sf::Color& getColour() const;


private:
	void m_defineProjectilePolygon(float towRadius, int towNumPts);
	
	sf::Vector2f m_startPos;
	sf::Vector2f m_endPos;
	sf::ConvexShape m_shape;

	sf::Vector2f m_position;
	float m_theta; //direction of travel (in rad)

	float m_speed;
	int m_attackedEnemyStaticIndex;
	attackType m_towerAttackType;
	int m_towerAttackStrength;
};


