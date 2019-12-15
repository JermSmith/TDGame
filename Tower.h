#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>

#include "Path.h"
#include "Enemy.h"
#include "ProjectileManager.h"


enum class attackType
{
	divide,
	subtract,
	root,
};

class Tower
{
public:
	Tower();

	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	virtual void update(std::vector<std::unique_ptr<Enemy>>* enemies);
	void render(sf::RenderTarget& renderer);

	const sf::Vector2f& getPosition() const;
	void setPosition(sf::Vector2f& position);

	const float& getRadius() const;
	void setRadius(float radius);

	const attackType& getAttackType() const;
	void setAttackType(attackType&);

	const float& getRange() const;
	void setRange(float&);

	//const sf::Time& getCooldown() const;
	//void setCooldown(sf::Time&);

	const int& getStrength() const;
	void setStrength(int&);

	const bool& getbIsClickedOn() const;
	void setbIsClickedOn(bool);

	// sets AttackType, Strength, Position, Radius, and Range, as well as graphics.
	void setBasicProperties(attackType type, int strength, sf::Vector2f position);

protected:
	// these are accessible by TowerSub/Div/Root and Cursor, but not others

	sf::Vector2f m_position;
	int m_strength;
	float m_radius;
	float m_range;

	sf::CircleShape m_towerCircle;
	sf::CircleShape m_rangeCircle;
	sf::Text m_strengthString;

	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_timePoint = m_timer.restart();
	sf::Time m_cooldownTime; //depends on m_rate
	bool m_bShouldResetElapsedTime = false;

	int m_numofAttacksInWave = 0;

	enum class targetPriority
	{
		close,
		first,
		last,
		strong,
		weak,
		largestPrime,
	};

	attackType m_attackType;
	targetPriority m_priority;
	unsigned int m_maxNumTargets;

	/* Before this function is called, the enemy in "enemies" at the index "enemyIndex" must be known to be in range of
	the tower and attackable by the attack type. Then the function either slots "enemyIndex" into the "enemyIndicesToAttack"
	vector at the proper position to maintain the sorting of most prioritized towers to least prioritized towers in the vector,
	or else it does not change "enemyIndices" if the enemy does not exceed priority criteria. Returns vector of enemy indices. */
	std::vector<int> m_possiblyAddEnemyIndexToVectorAndSort(std::vector<std::unique_ptr<Enemy>>* enemies, int enemyIndex, std::vector<int> enemyIndicesToAttack);

	ProjectileManager m_projectileManager;

	bool m_bIsClickedOn = true;

private:

};


