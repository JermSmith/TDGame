#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:

	void update() override;
	void render(sf::RenderTarget& renderer) override;


private:


};

