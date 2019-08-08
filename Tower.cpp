#include "Tower.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"
#include <algorithm>

Tower::Tower()
{

}

// (1)window, (2)attack type, (3)strength
Tower::Tower(const sf::RenderWindow& window, attackType type, int strength) // this constructor gets called when tower is actually placed in m_towers in World.cpp
{
	storeLogicData(type, strength, sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

	storeGraphicsData_TowerConstruction();
}

void Tower::storeLogicData(attackType type, int strength, sf::Vector2f position)
// sets AttackType, Strength, Radius, Range, Rate
{
	if (position != sf::Vector2f{ -1, -1 })
	{
		m_position = position;
		//position where the mouse is clicked; want this to be centre of circle
	}

	m_attackType = type;
	m_strength = strength;

	if (type == attackType::subtract || type == attackType::divide)
	{
		m_radius = 32.f;
		m_range = 128.f;
		m_rate = 1000;
	}
	else if (type == attackType::squareroot || type == attackType::cuberoot)
	{
		m_radius = 20.f;
		m_range = 200.f;
		m_rate = 1500;
	}
}

void Tower::storeGraphicsData_Cursor()
{
	m_towerCircle.setRadius(m_radius);
	m_towerCircle.setOrigin(sf::Vector2f(m_towerCircle.getRadius(), m_towerCircle.getRadius()));

	m_rangeCircle.setRadius(m_range);
	m_rangeCircle.setOrigin(sf::Vector2f(m_range, m_range));
}

void Tower::storeGraphicsData_TowerConstruction()
{
	// m_strengthString.setFontResourceHolder::get().fonts.get("stkaiti"));
	m_strengthString.setFont(ResourceHolder::get().fonts.get("arial"));
	m_strengthString.setPosition(m_position);
	m_strengthString.setFillColor(sf::Color::Red);

	m_towerCircle.setRadius(m_radius);
	m_towerCircle.setOrigin(sf::Vector2f(m_towerCircle.getRadius(), m_towerCircle.getRadius()));
	//origin is relative to the top left corner of the circle's surrounding "box"; here it is set to be the centre of circle
	m_towerCircle.setPosition(m_position); //origin of the circle goes to this position, which is location of click
	m_towerCircle.setFillColor(sf::Color::Cyan);

	m_rangeCircle.setRadius(m_range);
	m_rangeCircle.setOrigin(sf::Vector2f(m_range, m_range));
	m_rangeCircle.setPosition(m_position);
	m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));

	switch (m_attackType)
	{
	case attackType::divide:
		m_strengthString.setString("/ " + std::to_string(m_strength));
		break;

	case attackType::subtract:
		if (m_strength < 0) { m_strengthString.setString("+ " + std::to_string(m_strength)); }
		else { m_strengthString.setString("- " + std::to_string(m_strength)); }
		break;

	case attackType::squareroot:
		m_strengthString.setString("Sqrt");
		break;

	case attackType::cuberoot:
		m_strengthString.setString("Cbrt");
		break;

	default:
		break;
	}
}

void Tower::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	switch (e.type)
	{
	case sf::Event::EventType::MouseButtonReleased:

		break;

	default:
		break;
	}
}

void Tower::update(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	m_delayTime = sf::milliseconds(m_rate);
	m_elapsedTime = m_timer.getElapsedTime() - m_timePoint;

	if (m_elapsedTime > m_delayTime)
	{
		m_timePoint = m_timer.getElapsedTime();

		this->m_reduceEnemyHealth(enemies);
	}

	if (m_bIsClickedOn)
	{
		m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));
	}
	else { m_rangeCircle.setFillColor(sf::Color::Transparent); }
}

void Tower::m_reduceEnemyHealth(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	float distance;
	float minDistance = this->getRange(); //reset
	int enemyIndex = -1;

	// TODO: allow for different targeting preferences (divide,sqrt,cbrt: close or strong; plus,minus: weak or strongest prime)

	for (unsigned int i = 0; i < enemies->size(); i++)
	{
		distance = distanceBetweenPoints(
			enemies->at(i)->getPosition().x, enemies->at(i)->getPosition().y, m_position.x, m_position.y);

		if (distance <= m_range)
		{
			if (distance <= minDistance)
			{
				switch (m_attackType) // only doing these calculations for enemies in range
				{
				case attackType::divide:
					if (enemies->at(i)->getHealth() % m_strength == 0) // mod
					{
						minDistance = distance; //new minimum distance found
						enemyIndex = i;
					}
					break;
				case attackType::subtract:
					minDistance = distance; // new minumum distance found
					enemyIndex = i;
					break;
				case attackType::squareroot: // TODO: ensure does not attack enemy of health 1 or 0
					if (std::round(std::sqrt(enemies->at(i)->getHealth())) - std::sqrt(enemies->at(i)->getHealth()) == 0) // is a perfect square
					{
						minDistance = distance; // new minumum distance found
						enemyIndex = i;
					}
					break;
				case attackType::cuberoot: // TODO: ensure does not attack enemy of health 1 or 0
					if (std::round(std::cbrt(enemies->at(i)->getHealth())) - std::cbrt(enemies->at(i)->getHealth()) == 0) // is a perfect cube
					{
						minDistance = distance; // new minumum distance found
						enemyIndex = i;
					}
					break;
				default:
					break;
				}
			}
		}
	}
	if (enemyIndex != -1) //changed, so we found an enemy to attack
	{
		m_numofAttacksInWave++;

		switch (m_attackType)
		{
		case attackType::divide:
			enemies->at(enemyIndex)->setHealth(enemies->at(enemyIndex)->getHealth() / m_strength);
			break;
		case attackType::subtract:
			enemies->at(enemyIndex)->setHealth(enemies->at(enemyIndex)->getHealth() - m_strength);
			break;
		case attackType::squareroot:
			enemies->at(enemyIndex)->setHealth((int)std::sqrt(enemies->at(enemyIndex)->getHealth()));
			break;
		case attackType::cuberoot:
			enemies->at(enemyIndex)->setHealth((int)std::cbrt(enemies->at(enemyIndex)->getHealth()));
			break;
		default:
			break;
		}
	}
}

void Tower::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_rangeCircle);
	renderer.draw(m_towerCircle);
	renderer.draw(m_strengthString);
}

const sf::Vector2f& Tower::getPosition() const { return m_position; }
void Tower::setPosition(sf::Vector2f& position) { m_position = position; }

const float& Tower::getRadius() const { return m_radius; }
void Tower::setRadius(float radius) { m_radius = radius; }

const attackType Tower::getAttackType() const { return m_attackType; }
void Tower::setAttackType(attackType type) { m_attackType = type; }

float Tower::getRange() const { return m_range; }
void Tower::setRange(float range) { m_range = range; }

int Tower::getRate() const { return m_rate; }
void Tower::setRate(int rate) { m_rate = rate; }

int Tower::getStrength() const { return m_strength; }
void Tower::setStrength(int strength) { m_strength = strength; }

bool Tower::getbIsClickedOn() const { return m_bIsClickedOn; }
void Tower::setbIsClickedOn(bool tf) { m_bIsClickedOn = tf; }


