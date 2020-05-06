#pragma once
#include <memory>
#include "Projectile.h"
#include "Enemy.h"
#include "Util\Math.h"

class ProjectileManager
{
public:
	ProjectileManager();

	void update();

	// void handleEvent(sf::Event e);

	void render(sf::RenderTarget& renderer);

	void createProjectile(const std::unique_ptr<Enemy>& enemy, sf::Vector2f towerPos, sf::Color colour);

private:
	std::vector<std::unique_ptr<Projectile>> m_projectiles;
	float m_defaultProjSpeed;

};


