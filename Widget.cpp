#include "Widget.h"

namespace gui
{
	Widget::Text::Text()
	{
		setCharacterSize(15);
		setOutlineColor(sf::Color::Black);
		setFillColor(sf::Color::White);
		setFont(ResourceHolder::get().fonts.get("arial"));
	}

	void Widget::setText(const std::string& str) { m_text.setString(str); }

	sf::Vector2f Widget::getPosition() const { return m_position; }

	void Widget::setPosition(const sf::Vector2f& pos)
	{
		m_position = pos;
		InteractableShape::setPosition(m_position);

		m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 1.4f);
		m_text.setPosition(m_position);
	}
}



