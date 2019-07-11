#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:

	void update();
	void render(sf::RenderTarget& renderer) override;


private:


};
