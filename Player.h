#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:

	void update();
	void render(sf::RenderTarget& renderer) override;


private:


};

