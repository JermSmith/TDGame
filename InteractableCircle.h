#pragma once

#include "InteractableShape.h"

class InteractableCircle : public InteractableShape, public sf::CircleShape
{
public:
	//void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
	
	bool isRolledOn(const sf::RenderWindow& window) const override;
	sf::CircleShape* getCircle();	

private:
	sf::CircleShape m_circle;


};


