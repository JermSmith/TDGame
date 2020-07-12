#include "HoverMenu.h"
#include "Util\Math.h"

namespace gui
{
	HoverMenu::HoverMenu(const sf::Vector2f& topCentrePoint, float menuWidth, float outlineThickness, sf::Uint8 backgroundTransparency)
		: StackMenu(topCentrePoint, menuWidth, outlineThickness, backgroundTransparency)
	{
		m_widgetSpacer = 5;
	}

	void HoverMenu::updatePosition(const sf::RenderWindow& window)
	{
		// TODO: make menu stay within playing area when tower is too close to edge

		m_prevBasePosition = m_topCentrePoint;

		m_topCentrePoint = sf::Vector2f(
			window.mapPixelToCoords(sf::Mouse::getPosition(window)).x + sizes::HOVERMENU_X / 2,
			window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);

		sf::Vector2f posShift = sf::Vector2f(
			m_topCentrePoint.x - m_prevBasePosition.x,
			m_topCentrePoint.y - m_prevBasePosition.y);

		for (auto& wid : getWidgets())
		{
			wid->setPosition(sf::Vector2f(
				wid->getPosition().x + posShift.x,
				wid->getPosition().y + posShift.y));
		}

		m_background.setPosition(m_topCentrePoint.x - m_outerDim.x / 2, m_topCentrePoint.y);
	}
}



