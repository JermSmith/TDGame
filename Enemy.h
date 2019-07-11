#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(std::vector<sf::Vector2f> path, int health);
	
	int getHealth();
	void setHealth(int health);

	std::vector<sf::Vector2f> getVertices();
	void setVertices(std::vector<sf::Vector2f> vertices);

	float getSpeed();
	void setSpeed(float speed);

	sf::Vector2f getDirection();
	void setDirection(sf::Vector2f startPos, sf::Vector2f endPos);

	void update();
	void render(sf::RenderTarget& renderer) override;




private:
	int m_health;
	sf::Text m_healthString;

	float m_speed = (float)2; // pixels per second

	void updatePosition();

	std::vector<sf::Vector2f> m_vertices;
	
	unsigned int m_nextVertex = 1; // 1 is for its first destination vertex, and increases after arriving at each vertex

	sf::Vector2f m_direction; // unit vector describing direction of motion of enemy

	// m_position, m_size inherited from GameObject

	/*sf::Sprite m_sprite;*/
	sf::CircleShape m_circle;
};
