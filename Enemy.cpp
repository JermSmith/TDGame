#include "Enemy.h"
#include "Util\Math.h"
#include <iostream>
#include "ResourceManager\ResourceHolder.h"

/*Enemy::Enemy()
{
	
}*/

Enemy::Enemy(std::vector<sf::Vector2f> vertices, int health, float speed)
{
	m_bIsAlive = true;
	
	/*m_sprite.setTexture(ResourceHolder::get().textures.get("golem-walk"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));*/

	// m_healthString.setFont(ResourceHolder::get().fonts.get("stkaiti"));
	m_healthString.setFont(ResourceHolder::get().fonts.get("arial"));
	m_healthString.setFillColor(sf::Color::Yellow);

	m_circle.setRadius(16.);
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));

	m_vertices = vertices;
	m_health = health;
	m_speed = speed;

	m_position = m_vertices.at(0);
	setDirection(vertices.at(0), vertices.at(1)); // sets m_direction
}

const sf::Vector2f& Enemy::getPosition() const { return m_position; }
void Enemy::setPosition(sf::Vector2f& position) { m_position = position; }

const sf::Vector2f& Enemy::getSize() const { return m_size; }
void Enemy::setSize(sf::Vector2f& size) { m_size = size; }

int Enemy::getHealth() { return m_health; }
void Enemy::setHealth(int health) { m_health = health; }

bool Enemy::getbIsAlive() { return m_bIsAlive; }
//void Enemy::setbIsAlive(bool tf) { m_bIsAlive = tf; }

std::vector<sf::Vector2f> Enemy::getVertices() { return m_vertices; }
void Enemy::setVertices(std::vector<sf::Vector2f> vertices) { m_vertices = vertices; }

float Enemy::getSpeed() { return m_speed; }
void Enemy::setSpeed(float speed) { m_speed = speed; }

sf::Vector2f Enemy::getDirection() { return m_direction; }
// normalized so direction vector has length 1
void Enemy::setDirection(sf::Vector2f posA, sf::Vector2f posB)
{
	m_direction.x = (posB.x - posA.x) / distanceBetweenPoints(posA.x, posA.y, posB.x, posB.y);
	m_direction.y = (posB.y - posA.y) / distanceBetweenPoints(posA.x, posA.y, posB.x, posB.y);
}

void Enemy::updatePosition()
{
	m_position.x = m_position.x + m_direction.x * m_speed;
	m_position.y = m_position.y + m_direction.y * m_speed;

	if ((m_direction.x * m_position.x >= m_direction.x * m_vertices.at(m_nextVertex).x &&
		m_direction.y * m_position.y >= m_direction.y * m_vertices.at(m_nextVertex).y)
		||
		(abs(m_direction.x) < sin(PI / 9) &&    //moving vertically at an angle > 70 degrees, so only check that x-component has passed vertex
		m_direction.y * m_position.y > m_direction.y * m_vertices.at(m_nextVertex).y)
		||
		(abs(m_direction.y) < sin(PI / 9) &&    //moving horizontally at an angle < 20 degrees, so only check that y-component has passed vertex
		m_direction.x * m_position.x > m_direction.x * m_vertices.at(m_nextVertex).x))
		// note 1: multiply by m_direction.x or y to change direction of inequality for motion in a negative direction
		// note 2: >= means that for ortho path, x-component may always be equal (so true) but y-component will change from 
		//			false to true at some point (or vice versa). equal sign not necessary for path of arbitrary directions
	{
		m_nextVertex++; // enemy arrived at "next vertex", so select the next "next vertex"

		if (m_nextVertex == m_vertices.size())
		{
			// then cannot do m_vertices.at(m_nextVertex) because it is out of range
			// this means enemy has arrived at final vertex
			//this->setPosition(sf::Vector2f(0, 0));
			this->setSpeed(0);
			this->m_circle.setFillColor(sf::Color::Transparent);
			m_nextVertex = 0;
		}
		else { setDirection(m_vertices.at(m_nextVertex - 1), m_vertices.at(m_nextVertex)); }
	}
}


void Enemy::update()
{
	if (m_health <= 0)
	{
		m_bIsAlive = false;
	}
	
	updatePosition();

	m_healthString.setString(std::to_string(m_health));
	m_healthString.setPosition(m_position);

}

void Enemy::render(sf::RenderTarget& renderer)
{
	/*m_sprite.setPosition(m_position);
	renderer.draw(m_sprite);*/

	m_circle.setPosition(m_position);
	renderer.draw(m_circle);
	renderer.draw(m_healthString);

}


