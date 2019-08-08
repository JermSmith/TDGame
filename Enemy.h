#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class Enemy
{
public:
	//Enemy();
	Enemy(std::vector<sf::Vector2f> path, int health, float speed);
	
	const sf::Vector2f& getPosition() const;
	void setPosition(sf::Vector2f& position);

	const sf::Vector2f& getSize() const;
	void setSize(sf::Vector2f& size);

	int getHealth();
	void setHealth(int health);

	bool getbIsAlive();
	//void setbIsAlive(bool tf);

	std::vector<sf::Vector2f> getVertices();
	void setVertices(std::vector<sf::Vector2f> vertices);

	float getSpeed();
	void setSpeed(float speed);

	sf::Vector2f getDirection();
	void setDirection(sf::Vector2f startPos, sf::Vector2f endPos);

	void update();
	void render(sf::RenderTarget& renderer);




private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;

	int m_health;
	sf::Text m_healthString;

	bool m_bIsAlive;

	float m_speed; // pixels per update

	void updatePosition();

	std::vector<sf::Vector2f> m_vertices;
	
	unsigned int m_nextVertex = 1; // 1 is for its first destination vertex, and increases after arriving at each vertex

	sf::Vector2f m_direction; // unit vector describing direction of motion of enemy

	// m_position, m_size inherited from GameObject

	/*sf::Sprite m_sprite;*/
	sf::CircleShape m_circle;
};
