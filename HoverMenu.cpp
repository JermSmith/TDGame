#include "HoverMenu.h"
#include "Util\Math.h"

namespace gui
{
	HoverMenu::HoverMenu(const sf::Vector2f& topCentrePoint, float menuWidth, float outlineThickness
		, sf::Uint8 backgroundTransparency, int widgetSpacing)
		: StackMenu(topCentrePoint, menuWidth, outlineThickness, backgroundTransparency, widgetSpacing)
	{ }

	void HoverMenu::updatePosition(const sf::RenderWindow& window)
	{
		sf::Vector2f prevBasePosition = m_topCentrePoint;
		sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		// makes hover menu stay within playing area when tower is too close to edge
		if ((mousePos.x + m_background.getSize().x > sizes::WORLD_SIZE_X - sizes::PLAYINGMENU_X)
			&&
			(mousePos.y + m_background.getSize().y > sizes::WORLD_SIZE_Y))
		{
			m_topCentrePoint = sf::Vector2f(
				(float)(sizes::WORLD_SIZE_X - sizes::PLAYINGMENU_X) - m_background.getSize().x / 2,
				sizes::WORLD_SIZE_Y - m_background.getSize().y);
		}
		else if (mousePos.x + m_background.getSize().x > sizes::WORLD_SIZE_X - sizes::PLAYINGMENU_X)
		{
			m_topCentrePoint = sf::Vector2f(
				(float)(sizes::WORLD_SIZE_X - sizes::PLAYINGMENU_X) - m_background.getSize().x / 2,
				window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
		}
		else if (mousePos.y + m_background.getSize().y > sizes::WORLD_SIZE_Y)
		{
			m_topCentrePoint = sf::Vector2f(
				window.mapPixelToCoords(sf::Mouse::getPosition(window)).x + sizes::HOVERMENU_X / 2,
				sizes::WORLD_SIZE_Y - m_background.getSize().y);
		}
		else
		{
			m_topCentrePoint = sf::Vector2f(
				window.mapPixelToCoords(sf::Mouse::getPosition(window)).x + sizes::HOVERMENU_X / 2,
				window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
		}

		sf::Vector2f posShift = sf::Vector2f(
			m_topCentrePoint.x - prevBasePosition.x,
			m_topCentrePoint.y - prevBasePosition.y);

		for (auto& wid : getWidgets())
		{
			wid->setPosition(sf::Vector2f(
				wid->getPosition().x + posShift.x,
				wid->getPosition().y + posShift.y));
		}

		m_background.setPosition(m_topCentrePoint.x - m_outerDim.x / 2, m_topCentrePoint.y);
	}
}



