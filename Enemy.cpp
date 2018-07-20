#include "Enemy.h"
#include "Util\Math.h"

// constructors

Enemy::Enemy()
{
	m_sprite.setTexture(ResourceHolder::get().textures.get("golem-walk"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}
Enemy::Enemy(int health)
{
	m_sprite.setTexture(ResourceHolder::get().textures.get("golem-walk"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	
	m_health = health;
}
Enemy::Enemy(std::vector<sf::Vector2f> vertices)
{
	m_sprite.setTexture(ResourceHolder::get().textures.get("golem-walk"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	
	m_vertices = vertices;

	m_position = vertices.at(0); // assumes path has at least 1 vertex
	setDirection(vertices.at(0), vertices.at(1)); // sets m_direction
}
Enemy::Enemy(std::vector<sf::Vector2f> vertices, int health)
{
	m_sprite.setTexture(ResourceHolder::get().textures.get("golem-walk"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	
	m_vertices = vertices;
	m_health = health;

	m_position = m_vertices.at(0);
	setDirection(vertices.at(0), vertices.at(1)); // sets m_direction
}


int Enemy::getHealth() { return m_health; }
void Enemy::setHealth(int health) { m_health = health; }

std::vector<sf::Vector2f> Enemy::getVertices() { return m_vertices; }
void Enemy::setVertices(std::vector<sf::Vector2f> vertices) { m_vertices = vertices; }

int Enemy::getSpeed() { return m_speed; }
void Enemy::setSpeed(int speed) { m_speed = speed; }

sf::Vector2f Enemy::getDirection() { return m_direction; }
// normalized so direction vector has length 1
void Enemy::setDirection(sf::Vector2f posA, sf::Vector2f posB)
{
	//float distanceAtoB = sqrtf((posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y));

	m_direction.x = (posB.x - posA.x) / distanceBetweenPoints(posA.x, posA.y, posB.x, posB.y);
	m_direction.y = (posB.y - posA.y) / distanceBetweenPoints(posA.x, posA.y, posB.x, posB.y);
}


void Enemy::update()
{
	
	// need to incorporate destinations for switching direction
	
	m_position.x = m_position.x + m_direction.x * m_speed;
	m_position.y = m_position.y + m_direction.y * m_speed;
	
}

void Enemy::render(sf::RenderTarget& renderer)
{
	m_sprite.setPosition(m_position);
	renderer.draw(m_sprite);


}


