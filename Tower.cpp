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
	
}

void Tower::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_rangeCircle);
	renderer.draw(m_towerCircle);
	renderer.draw(m_strengthString);

	m_projectileManager.render(renderer);
}

/* Before this function is called, the enemy in "enemies" at the index "enemyIndex" must be known to be in range of
the tower and attackable by the attack type. Then the function either slots "enemyIndex" into the "enemyIndices"
vector at the proper position to maintain the sorting of strongest towers to weakest towers in the vector, or else
it does not change "enemyIndices" if the enemy does not exceed priority criteria. Returns vector of enemy indices. */
std::vector<int> Tower::m_possiblyAddEnemyIndexToVectorAndSort(std::vector<std::unique_ptr<Enemy>>* enemies, int a_enemyIndex, std::vector<int> a_enemyIndices)
{
	int i_e = a_enemyIndex;
	std::vector<int> enemyIndices = a_enemyIndices;

	// TODO: allow for different targeting preferences:
	// closest				(all)
	// first				(all)
	// last					(all)
	// strongest			(all)
	// weakest				(all)
	// largest prime		(+ -)

	float distanceToBeat; // used for "closest" priority
	float enemyDistance; // used for "closest" priority

	switch (m_priority)
	{
	case targetPriority::close:
		distanceToBeat = m_range; //reset to "max", but can get smaller as closer enemies are found
		enemyDistance = distanceBetweenPoints(enemies->at(i_e)->getPosition(), m_position);

		// The enemy indices are placed into "enemyIndices" in such a way that the index at position 0 is the closest enemy,
		// and the index at position "numEnemiesToAttack" (or otherwise at the back, if num enemies in range is less than
		// numEnemiesToAttack) is the furthest enemy
		if (enemyDistance < distanceToBeat) // "closest" priority search criteria
											// note that if enemyDistance is equal to distance to beat (e.g. two enemies are tied for distance), the target will not change
		{
			if (enemyIndices.size() == 0) // first enemy to be added
			{
				enemyIndices.push_back(i_e);
				if (enemyIndices.size() < m_numEnemiesToAttack)
				{
					distanceToBeat = m_range; // can still accept an enemy that is more distant than those already included, since
											  // vector still has room to grow
				}
				else
				{
					distanceToBeat = distanceBetweenPoints(enemies->at(enemyIndices.back())->getPosition(), m_position);
				}
			}

			else if (enemyIndices.size() < m_numEnemiesToAttack) // insert an index into enemyIndices without removing any of them
			{
				bool bIndexInsertedIntoVector = false;
				int j_wh = 0; // iterator for vector of indices (same as # of times while has looped)

				while (!bIndexInsertedIntoVector)
				{// compare distance of enemy (i_e) with distances of enemies already stored (j_wh)
					if (j_wh == enemyIndices.size()) // the end of the vector
					{
						enemyIndices.push_back(i_e); // insert i_e at the end of enemyIndices
						if (m_numEnemiesToAttack > enemyIndices.size()) { distanceToBeat = m_range; }
						else {
							distanceToBeat = distanceBetweenPoints(enemies->at(enemyIndices.back())->getPosition(), m_position);
						}
						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else if (distanceBetweenPoints(enemies->at(enemyIndices.at(j_wh))->getPosition(), m_position) > enemyDistance)
					{
						// if here, then the distance from tower to enemy (not yet in index vector) is less than
						// the distance from tower to enemy at position j_wh (which is already in index vector)
						enemyIndices.insert(enemyIndices.begin() + j_wh, i_e); // insert index i_e at position j_wh
						if (m_numEnemiesToAttack > enemyIndices.size()) { distanceToBeat = m_range; }
						else {
							distanceToBeat = distanceBetweenPoints(enemies->at(enemyIndices.back())->getPosition(), m_position);
						}
						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						j_wh++;
					}
				}
			}

			else if (enemyIndices.size() == m_numEnemiesToAttack) // the vector size is maxxed out, so the currently last index will be popped
			{
				bool bIndexInsertedIntoVector = false;
				int j_wh = 0; // iterator for vector of indices (same as # of times while has looped)

				while (!bIndexInsertedIntoVector)
				{// compare distance of enemy (i_e) with distances of enemies already stored (j_wh)
					if (distanceBetweenPoints(enemies->at(enemyIndices.at(j_wh))->getPosition(), m_position) > enemyDistance)
					{
						// if here, then the distance from tower to enemy (not yet in index vector) is less than
						// the distance from tower to enemy at position j_wh (which is already in index vector)
						enemyIndices.insert(enemyIndices.begin() + j_wh, i_e); // insert index i_e at position j_wh
						enemyIndices.pop_back(); // remove the last element, since distance is too large -- the final index must be
												 // popped AFTER the insertion, not before, or else the insertion will be out of range in the case of inserting
												 // immediately before the final index
						distanceToBeat = distanceBetweenPoints(enemies->at(enemyIndices.back())->getPosition(), m_position);
						// the most distant enemy that is still included to be attacked is at the end of enemyIndices
						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						j_wh++;
					}
				}
			}

			break;
	case targetPriority::first:


		break;
	case targetPriority::last:


		break;
	case targetPriority::strong:


		break;
	case targetPriority::weak:


		break;
	case targetPriority::largestPrime:


		break;
		}
	}

	return enemyIndices;
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



