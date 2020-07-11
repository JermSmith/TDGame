#include "Widget.h"
#include "Util\Math.h"

namespace gui
{
	//Text
	Widget::Text::Text()
	{
		setCharacterSize(15);
		setOutlineColor(sf::Color::Black);
		setFillColor(sf::Color::White);
		setFont(ResourceHolder::get().fonts.get("arial"));
	}

	void Widget::setText(const std::string& str) { m_text.setString(str); }

	//bool Widget::Rectangle::isRolledOn(const sf::RenderWindow& window) const
	/*bool Widget::isRolledOn(const sf::RenderWindow& window) const
	{
		auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		
		return getGlobalBounds().contains((float)pos.x, (float)pos.y);
	}*/

	//bool Widget::Rectangle::isClicked(sf::Event e, const sf::RenderWindow& window)
	/*bool Widget::isClicked(sf::Event e, const sf::RenderWindow& window)
	{
		if (isRolledOn(window))
		{
			if (e.type == sf::Event::MouseButtonPressed)
			{
				return e.mouseButton.button == sf::Mouse::Left; // returns true if mouse button is left click
			}
		}
		return false;
	}*/
}

