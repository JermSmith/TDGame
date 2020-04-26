#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
//#include "GUI\InteractableCircle.h"
#include "GUI\InteractableShape.h"

class Enemy : public InteractableShape
{
public:
	Enemy(std::vector<sf::Vector2f> path, int health, float speed);
	
	const sf::Vector2f& getPosition() const;
	void setPosition(sf::Vector2f& position);

	const sf::Vector2f& getSize() const;
	void setSize(sf::Vector2f& size);

	const int& getHealth() const;
	void setHealth(int health);

	const bool& getbIsAlive() const;
	const bool& getbReachedTheEnd() const;

	const std::vector<sf::Vector2f>& getVertices() const;
	void setVertices(std::vector<sf::Vector2f> vertices);

	const sf::Vector2f& getNextDest() const;

	const float& getSpeed() const;
	void setSpeed(float speed);

	const float& getTheta() const;

	// temporary for debugging
	void resetFillColor();
	void setFillColor(sf::Color color);

	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& renderer);




private:
	sf::Vector2f m_position;
	sf::Vector2f m_size;

	int m_health;	

	sf::Text m_healthString;

	sf::Color m_defaultFillColor = sf::Color::Red;

	bool m_bIsAlive;
	bool m_bReachedTheEnd;

	float m_speed; // pixels per update
	float m_theta; // direction of travel

	void m_updatePosition();
	void m_updateText();

	std::vector<sf::Vector2f> m_vertices;
	
	unsigned int m_nextVertexIndex; // 1 is for its first destination vertex, and increases after arriving at each vertex

	/*sf::Sprite m_sprite;*/
	//sf::CircleShape m_circle;
};

