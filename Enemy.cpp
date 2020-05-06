#include "Enemy.h"
#include "Util\Math.h"
#include <iostream>
#include "ResourceManager\ResourceHolder.h"

Enemy::Enemy(std::vector<sf::Vector2f> vertices, int health, float speed) : InteractableShape(16.f, 50)
{
	m_bIsAlive = true;
	m_bReachedTheEnd = false;

	/*m_sprite.setTexture(ResourceHolder::get().textures.get("golem-walk"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));*/

	// m_healthString.setFont(ResourceHolder::get().fonts.get("stkaiti"));

	m_healthString.setFont(ResourceHolder::get().fonts.get("arial"));
	m_healthString.setFillColor(sf::Color::Yellow);
	//InteractableShape::setFillColour(m_defaultFillColor);
	InteractableShape::setFillColour(sf::Color::Red);

	m_vertices = vertices;
	m_health = health;
	m_speed = speed;

	m_position = m_vertices.at(0);
	m_theta = atan2f(vertices.at(1).y - vertices.at(0).y, vertices.at(1).x - vertices.at(0).x);

	m_nextVertexIndex = 1; // 1 is for its first destination vertex, and increases after arriving at each vertex

}

const sf::Vector2f& Enemy::getPosition() const { return m_position; }
void Enemy::setPosition(sf::Vector2f& position) { m_position = position; }

const float& Enemy::getRadius() const { return InteractableShape::getPrimaryDim(); }

const int& Enemy::getHealth() const { return m_health; }
void Enemy::setHealth(int health) { m_health = health; }

const bool& Enemy::getbIsAlive() const { return m_bIsAlive; }
const bool& Enemy::getbReachedTheEnd() const { return m_bReachedTheEnd; }

const std::vector<sf::Vector2f>& Enemy::getVertices() const { return m_vertices; }
void Enemy::setVertices(std::vector<sf::Vector2f> vertices) { m_vertices = vertices; }

const sf::Vector2f& Enemy::getNextDest() const { return m_vertices.at(m_nextVertexIndex); }

const float& Enemy::getSpeed() const { return m_speed; }
void Enemy::setSpeed(float speed) { m_speed = speed; }

const float& Enemy::getTheta() const { return m_theta; }

const bool& Enemy::getbIsClickedOn() const { return m_bIsClickedOn; }
void Enemy::setbIsClickedOn(bool tf) { m_bIsClickedOn = tf; }

void Enemy::m_updatePosition()
{
	m_position.x = m_position.x + cosf(m_theta) * m_speed;
	m_position.y = m_position.y + sinf(m_theta) * m_speed;

	if ((m_position.x * cosf(m_theta) >= m_vertices.at(m_nextVertexIndex).x * cosf(m_theta) &&
		m_position.y * sinf(m_theta) >= m_vertices.at(m_nextVertexIndex).y * sinf(m_theta))
		||
		//moving vertically at an angle > 70 degrees, so only check that x-component has passed vertex
		(abs(cosf(m_theta)) < sin(PI / 9) && // horizontal component is small
			m_position.y * sinf(m_theta) > m_vertices.at(m_nextVertexIndex).y * sinf(m_theta))
		||
		//moving horizontally at an angle < 20 degrees, so only check that y-component has passed vertex
		(abs(sinf(m_theta)) < sin(PI / 9) && // vertical component is small 
			m_position.x * cosf(m_theta) > m_vertices.at(m_nextVertexIndex).x * cosf(m_theta)))
		// note 1: multiply by m_direction.x or y to change direction of inequality for motion in a negative direction
		// note 2: >= means that for ortho path, x-component may always be equal (so true) but y-component will change from 
		//			false to true at some point (or vice versa). equal sign not necessary for path of arbitrary directions
	{
		m_nextVertexIndex++; // enemy arrived at "next vertex", so select the next "next vertex"

		if (m_nextVertexIndex == m_vertices.size())
		{
			// then cannot do m_vertices.at(m_nextVertex) because it is out of range
			// this means enemy has arrived at final vertex
			//setSpeed(0);
			m_nextVertexIndex = 0;
			m_bReachedTheEnd = true;
		}
		else
		{
			float dy = m_vertices.at(m_nextVertexIndex).y - m_vertices.at(m_nextVertexIndex - 1).y;
			float dx = m_vertices.at(m_nextVertexIndex).x - m_vertices.at(m_nextVertexIndex - 1).x;
			m_theta = atan2f(dy , dx);
		}
	}
}

void Enemy::m_updateText()
{
	m_healthString.setString(std::to_string(m_health));
	m_healthString.setOrigin(m_healthString.getGlobalBounds().width / (float)2, m_healthString.getGlobalBounds().height / (float)1.25);
	m_healthString.setStyle(sf::Text::Bold);
	m_healthString.setPosition(m_position);
	
	if (m_health < 10) { m_healthString.setCharacterSize(30); }
	else if (m_health < 100) { m_healthString.setCharacterSize(25); }
	else if (m_health < 1000) { m_healthString.setCharacterSize(20); }
	else { m_healthString.setCharacterSize(15); }
}

void Enemy::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	switch (e.type)
	{
	case sf::Event::MouseMoved:
		
		break;
		
	case sf::Event::MouseButtonPressed:

		break;

	default:
		break;
	}
}

void Enemy::update(const sf::RenderWindow& window)
{
	if (m_health <= 0)
	{
		m_bIsAlive = false;
	}
	
	m_updatePosition();
	m_updateText();
	
	if (m_bIsClickedOn)
	{
		InteractableShape::setClickedAppearance();
	}
	else
	{
		InteractableShape::removeClickedAppearance();
	}

	if (isRolledOn(window))
	{
		InteractableShape::setRolledAppearance();
	}
	else if (!m_bIsClickedOn)
	{
		InteractableShape::removeRolledAppearance();
	}
	
	//if (bIsPrime(m_health))
	//{
	//	m_circle.setFillColor(sf::Color::White);
	//}
	//if (!bIsPrime(m_health))
	//{
	//	m_circle.setFillColor(m_defaultFillColor);
	//}

}

void Enemy::render(sf::RenderTarget& renderer)
{
	InteractableShape::setPosition(m_position);
	InteractableShape::render(renderer);
	renderer.draw(m_healthString);
}


