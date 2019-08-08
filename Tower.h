#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>

#include "Path.h"
#include "Enemy.h"


enum class attackType
{
divide,
subtract,
squareroot,
cuberoot,
none,
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

	const attackType getAttackType() const;
	void setAttackType(attackType);

	float getRange() const;
	void setRange(float);

	int getRate() const;
	void setRate(int);

	int getStrength() const;
	void setStrength(int);

	bool getbIsClickedOn() const;
	void setbIsClickedOn(bool);

protected:
	sf::Vector2f m_position;
	float m_radius;
	float m_range;

	sf::CircleShape m_towerCircle;
	sf::CircleShape m_rangeCircle;



private:
	void storeGraphicsData_TowerConstruction();

	attackType m_attackType;
	int m_strength;
	int m_rate;

	sf::Text m_strengthString;

	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_timePoint = m_timer.restart();
	sf::Time m_delayTime; //depends on m_rate

	int m_numofAttacksInWave = 0;
	
	void m_reduceEnemyHealth(std::vector<std::unique_ptr<Enemy>>* enemies);
	
	bool m_bIsClickedOn = true;

};