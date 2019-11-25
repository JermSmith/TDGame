#include "Tower.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"
#include <algorithm>

Tower::Tower() {} // necessary, so that Cursor inherits a default constructor

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

	switch (type)
	{
	case attackType::subtract:
		m_radius = 32.f;
		m_range = 128.f;
		m_cooldownTime = sf::milliseconds(1000);
		break;

	case attackType::divide:
		m_radius = 32.f;
		m_range = 150.f;
		m_cooldownTime = sf::milliseconds(1000);
		break;

	case attackType::root:
		m_radius = 20.f;
		m_range = 200.f;
		m_cooldownTime = sf::milliseconds(1500);
		break;
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

	m_rangeCircle.setRadius(m_range);
	m_rangeCircle.setOrigin(sf::Vector2f(m_range, m_range));
	m_rangeCircle.setPosition(m_position);
	m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));

	switch (m_attackType)
	{
	case attackType::divide:
		m_strengthString.setString("/ " + std::to_string(m_strength));
		m_towerCircle.setFillColor(sf::Color::Cyan);
		break;

	case attackType::subtract:
		if (m_strength < 0) { m_strengthString.setString("+ " + std::to_string(m_strength)); }
		else { m_strengthString.setString("- " + std::to_string(m_strength)); }
		m_towerCircle.setFillColor(sf::Color::Magenta);
		break;

	case attackType::root:
		if (m_strength == 2)
		{
			m_strengthString.setString("Sqrt");
			m_towerCircle.setFillColor(sf::Color::Magenta);
		}
		else if (m_strength == 3)
		{
			m_strengthString.setString("Cbrt");
			m_towerCircle.setFillColor(sf::Color::Cyan);
		}
		else
		{
			m_strengthString.setString(std::to_string(m_strength) + "th root");
			m_towerCircle.setFillColor(sf::Color::Cyan);
		}

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
	m_elapsedTime = m_timer.getElapsedTime() - m_timePoint;
	
	if (m_elapsedTime > m_cooldownTime)
	{
		// projectiles also created in this function
		m_attackEnemies(enemies);

		if (m_bShouldResetElapsedTime) // essentially reset m_elapsedTime to 0 (see above)
		{
			m_timePoint = m_timer.getElapsedTime();
			m_bShouldResetElapsedTime = false;
		}
	}

	if (m_bIsClickedOn)
	{
		m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));
	}
	else { m_rangeCircle.setFillColor(sf::Color::Transparent); }

	m_projectileManager.update();
}

void Tower::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_rangeCircle);
	renderer.draw(m_towerCircle);
	renderer.draw(m_strengthString);

	m_projectileManager.render(renderer);
}

void Tower::m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies)
{
	float distance;
	float minDistance = m_range; //reset
	int enemyIndex = -1;

	

	// TODO: allow for different targeting preferences:
	// closest				(all)
	// first				(all)
	// last					(all)
	// strongest			(all)
	// weakest				(all)
	// largest prime		(+ -)

	// TODO: make it so there is a different class for each tower attack type, each inheriting from tower. When determining
	//which enemy to attack, create a vector to store the enemies. It SHOULD be preset how many enemies will be attacked, so the
	//tower can attack the one (or two, three, etc.) closest (or strongest, furthest, etc.) tower(s)

	for (unsigned int i = 0; i < enemies->size(); i++)
	{
		distance = distanceBetweenPoints(enemies->at(i)->getPosition(), m_position);
		
		if (distance <= m_range)
		{
			if (distance <= minDistance)
			{
				switch (m_attackType) // only doing these calculations for enemies in range
				{
				case attackType::divide:
					if (enemies->at(i)->getHealth() > 1) // ensure does not attack enemy of health 1 or 0
					{
						if (enemies->at(i)->getHealth() % m_strength == 0) // mod
						{
							minDistance = distance; //new minimum distance found
							enemyIndex = i;
						}
					}
					break;

				case attackType::subtract:
					minDistance = distance; // new minumum distance found
					enemyIndex = i;
					break;

				case attackType::root:
					if (enemies->at(i)->getHealth() > 1) // ensure does not attack enemy of health 1 or 0
					{
						double val1 = std::round(std::pow(enemies->at(i)->getHealth(), 1. / double(m_strength)));
						double val2 = std::pow(enemies->at(i)->getHealth(), 1. / double(m_strength));

						if (abs(val1 - val2) < 1e-7) // is a perfect nth root
						{
							minDistance = distance; // new minumum distance found
							enemyIndex = i;
						}
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
		m_numofAttacksInWave++; // for stat collection purposes
		m_bShouldResetElapsedTime = true;

		m_projectileManager.createProjectile(enemies->at(enemyIndex), m_position, m_towerCircle.getFillColor());

		switch (m_attackType)
		{
		case attackType::divide:
			enemies->at(enemyIndex)->setHealth(enemies->at(enemyIndex)->getHealth() / m_strength);
			break;
		case attackType::subtract:
			enemies->at(enemyIndex)->setHealth(enemies->at(enemyIndex)->getHealth() - m_strength);
			break;
		case attackType::root:
			enemies->at(enemyIndex)->setHealth((int)std::pow(enemies->at(enemyIndex)->getHealth(), 1. / double(m_strength)));
			break;
		default:
			break;
		}
	}
	
}


const sf::Vector2f& Tower::getPosition() const { return m_position; }
void Tower::setPosition(sf::Vector2f& position) { m_position = position; }

const float& Tower::getRadius() const { return m_radius; }
void Tower::setRadius(float radius) { m_radius = radius; }

const attackType& Tower::getAttackType() const { return m_attackType; }
void Tower::setAttackType(attackType& type) { m_attackType = type; }

const float& Tower::getRange() const { return m_range; }
void Tower::setRange(float& range) { m_range = range; }

//const sf::Time& Tower::getCooldown() const { return m_cooldownTime; }
//void Tower::setCooldown(sf::Time& cooldown) { m_cooldownTime = cooldown; }

const int& Tower::getStrength() const { return m_strength; }
void Tower::setStrength(int& strength) { m_strength = strength; }

const bool& Tower::getbIsClickedOn() const { return m_bIsClickedOn; }
void Tower::setbIsClickedOn(bool tf) { m_bIsClickedOn = tf; }




