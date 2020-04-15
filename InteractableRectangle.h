#pragma once

#include "InteractableShape.h"

class InteractableRectangle : public InteractableShape, public sf::RectangleShape
{
public:
	bool isRolledOn(const sf::RenderWindow& window) const override;


private:


};