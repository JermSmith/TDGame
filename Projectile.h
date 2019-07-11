#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:

	void update();
	void render(sf::RenderTarget& renderer) override;


private:


};
