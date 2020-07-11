#include "Banner.h"
#include "Util\Math.h"

namespace gui
{
	Banner::Banner(float width, float height) 
		: InteractableShape(width, height) // this line calls InteractableShape constructor
	{
		InteractableShape::setOutlineThickness(-2);
		InteractableShape::setOutlineColour(sf::Color::White);
		InteractableShape::setFillColour(sf::Color::Transparent);
	}

	void Banner::setText(const std::string& str) { m_text.setString(str); }

	void Banner::handleEvent(sf::Event e, const sf::RenderWindow& window) {}

	void Banner::render(sf::RenderTarget& renderer)
	{
		InteractableShape::render(renderer);
		renderer.draw(m_text);
	}

	void Banner::update(const sf::RenderWindow& window)
	{

	}

	void Banner::setPosition(const sf::Vector2f& pos)
	{
		m_position = pos;
		InteractableShape::setPosition(m_position);

		m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 1.4f);
		m_text.setPosition(m_position);
	}

	sf::Vector2f Banner::getSize() const
	{
		//return m_rect.getSize();
		return sf::Vector2f(InteractableShape::getGlobalBounds().width
			, InteractableShape::getGlobalBounds().height);
	}

	int Banner::getMaxNumInRow() const { return 1; }

	// first column has index=0
	int Banner::getPositionInRow() const { return m_positionInRow; }
	// first column has index=0
	void Banner::setPositionInRow(const int num) { m_positionInRow = num; }

}


