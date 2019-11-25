#pragma once
#include <SFML\Graphics.hpp>
#include "GameObjects\Tower.h"

class TowerRoot : public Tower
{
public:

	TowerRoot(const sf::RenderWindow& window, attackType type, int strength);


private:


};