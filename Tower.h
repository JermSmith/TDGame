#pragma once
#include "GameObject.h"

class Tower : public GameObject
{
public:
	Tower();


	void update() override;
	void render(sf::RenderTarget& renderer) override;


private:

	sf::CircleShape m_circle;




};