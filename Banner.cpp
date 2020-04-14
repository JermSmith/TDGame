#include "Banner.h"
#include "Util\Math.h"

namespace gui
{
	Banner::Banner()
	{
		m_rect.setSize(sf::Vector2f((float)sizes::PLAYINGMENU_X, 48));
		m_rect.setOrigin(m_rect.getSize().x / 2, m_rect.getSize().y / 2);

		m_rect.setOutlineThickness(-2);
		m_rect.setOutlineColor(sf::Color::White);
		m_rect.setFillColor(sf::Color::Transparent);
		
		m_text.setOutlineThickness(2);
		m_text.setCharacterSize(30);
	}

	void Banner::setText(const std::string& str)
	{
		m_text.setString(str);
	}

	void Banner::handleEvent(sf::Event e, const sf::RenderWindow& window) {}

	void Banner::render(sf::RenderTarget& renderer)
	{
		renderer.draw(m_rect);
		renderer.draw(m_text);
	}

	void Banner::setPosition(const sf::Vector2f& pos)
	{
		m_position = pos;

		m_rect.setPosition(m_position);

		m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 1.4f);
		m_text.setPosition(m_position);
	}

	sf::Vector2f Banner::getSize() const { return m_rect.getSize(); }

	int Banner::getMaxNumInRow() const { return 1; }

	// first column has index=0
	int Banner::getPositionInRow() const { return m_positionInRow; }
	// first column has index=0
	void Banner::setPositionInRow(const int num) { m_positionInRow = num; }
}



