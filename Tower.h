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
	
	Tower(const sf::RenderWindow& window, attackType type, int strength);

	void storeLogicData(attackType type, int strength, sf::Vector2f position = { -1, -1 });
	void storeGraphicsData_Cursor();

	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void update(std::vector<std::unique_ptr<Enemy>>* enemies);
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

protected:
	sf::Vector2f m_position;
	float m_radius;
	float m_range;

	sf::CircleShape m_towerCircle;
	sf::CircleShape m_rangeCircle;

private:	
	void storeGraphicsData_TowerConstruction();

	ProjectileManager m_projectileManager;

	attackType m_attackType;
	int m_strength;

	sf::Text m_strengthString;

	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_timePoint = m_timer.restart();
	sf::Time m_cooldownTime; //depends on m_rate
	bool m_bShouldResetElapsedTime = false;

	int m_numofAttacksInWave = 0;
	
	void m_attackEnemies(std::vector<std::unique_ptr<Enemy>>* enemies);
	//void m_reduceEnemyHealth(std::vector<std::unique_ptr<Enemy>>* enemies);
	
	bool m_bIsClickedOn = true;

};