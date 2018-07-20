#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(int health);
	Enemy(std::vector<sf::Vector2f> path);
	Enemy(std::vector<sf::Vector2f> path, int health);
	
	int getHealth();
	void setHealth(int health);

	std::vector<sf::Vector2f> getVertices();
	void setVertices(std::vector<sf::Vector2f> vertices);

	int getSpeed();
	void setSpeed(int speed);

	sf::Vector2f getDirection();
	void setDirection(sf::Vector2f startPos, sf::Vector2f endPos);

	void update() override;
	void render(sf::RenderTarget& renderer) override;




private:
	int m_health = 24;

	int m_speed = 4; // pixels per second

	std::vector<sf::Vector2f> m_vertices;

	sf::Vector2f m_direction;

	// m_position, m_size inherited from GameObject

	sf::Sprite m_sprite;
};
