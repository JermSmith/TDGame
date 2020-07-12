#pragma once

#include "StackMenu.h"

namespace gui
{
	class HoverMenu : public StackMenu
	{
	public:
		HoverMenu(const sf::Vector2f& topCentrePoint, float menuWidth, float outlineThickness, sf::Uint8 backgroundTransparency);
		
		void updatePosition(const sf::RenderWindow& window);


	private:
		sf::Vector2f m_prevBasePosition;

	};
}



