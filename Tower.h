#pragma once
#include "GameObject.h"
#include "Path.h"
#include "Enemy.h"
#include <memory>

enum class attackType
{
divide,
subtract,
squareroot,
cuberoot
};

class Tower : public GameObject
{
public:
	Tower();
	Tower(const sf::RenderWindow& window);
	Tower(const sf::RenderWindow& window, attackType type, int strength, int range, int rate);

	void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
	void update(std::vector<std::unique_ptr<Enemy>>& enemies);
	void render(sf::RenderTarget& renderer) override;

	bool bInterferesWithScene(std::vector<std::unique_ptr<Tower>>& towers, Path& path, const sf::RenderWindow& window);

	int getRange();
	void setRange(int);

	int getStrength();
	void setStrength(int);

private:
	
	attackType m_attackType;
	int m_strength;
	int m_range;
	int m_rate;

	sf::Text m_strengthString;

	sf::Clock m_timer;
	sf::Time m_elapsedTime;
	sf::Time m_timePoint = m_timer.restart();
	sf::Time m_delayTime; //depends on m_rate

	void reduceEnemyHealth(std::vector<std::unique_ptr<Enemy>>& enemies);

	sf::CircleShape m_circle;
	
	

};