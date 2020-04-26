#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Projectile
{
public:
	Projectile(sf::Vector2f startPos, sf::Vector2f endPos, float speed, sf::Color colour);

	void update();
	void render(sf::RenderTarget& renderer);

	const sf::Vector2f& getPosition() const;
	void setPosition(sf::Vector2f&);

	const sf::Vector2f& getEndPos() const;


private:
	sf::Vector2f m_startPos;
	sf::Vector2f m_endPos;
	sf::CircleShape m_circle;

	sf::Vector2f m_position;
	float m_theta; //direction of travel (in rad)

	float m_speed;
};
