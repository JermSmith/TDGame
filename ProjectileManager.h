#pragma once
#include <memory>
#include "Projectile.h"
#include "Enemy.h"
#include "Util\Math.h"

class ProjectileManager
{
public:
	ProjectileManager();

	void update(std::vector<std::unique_ptr<Enemy>>* enemies);

	// void handleEvent(sf::Event e);

	void render(sf::RenderTarget& renderer);

	void createProjectile(
		const std::unique_ptr<Enemy>& enemy, sf::Vector2f towPos, attackType towAttackType
		, int towAttackStrength, sf::Color towColour, float towRadius, int towNumPts);

private:
	std::vector<std::unique_ptr<Projectile>> m_projectiles;
	float m_defaultProjSpeed;

};


