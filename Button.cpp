#include "Button.h"
#include "Util\Math.h"
#include <iostream>
//#include "Util\ColourManager.h"

namespace gui
{
	Button::Button(const float& radius, const int& numPts)
		: InteractableShape(radius, numPts) // this line calls InteractableShape constructor
	{
		InteractableShape::setOutlineThickness(-2);
		InteractableShape::setOutlineColour(sf::Color::Green);
		InteractableShape::setFillColour(sf::Color::Black);
	}

	Button::Button(const float& width, const float& height)
		: InteractableShape(width, height) // this line calls InteractableShape constructor
	{
		InteractableShape::setOutlineThickness(-2);
		InteractableShape::setOutlineColour(sf::Color::Green);
		InteractableShape::setFillColour(sf::Color::Black);
	}

	void Button::setFunction(std::function<void(void)> func) { m_function = func; }

	void Button::setText(const std::string& str) { m_text.setString(str); }

	void Button::setTexture(const sf::Texture& tex) { InteractableShape::setTexture(tex); }

	void Button::update(const sf::RenderWindow& window)
	{
		if (isRolledOn(window)) { setFillColour(sf::Color(51, 51, 51)); }
		else { setFillColour(sf::Color::Black); }
	}

	void Button::handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		switch (e.type)
		{
		case sf::Event::MouseButtonPressed:
			switch (e.mouseButton.button)
			{
			case sf::Mouse::Left:
				if (isRolledOn(window)) // if distance is less than radius
				{
					m_function();
				}
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}

	void Button::render(sf::RenderTarget& renderer)
	{
		InteractableShape::render(renderer);
		renderer.draw(m_text);
	}

	void Button::setPosition(const sf::Vector2f& pos)
	{
		m_position = pos;

		InteractableShape::setPosition(m_position);

		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 1.25f);
		m_text.setPosition(m_position);
	}

	sf::Vector2f Button::getSize() const
	{
		return sf::Vector2f(InteractableShape::getGlobalBounds().width
			, InteractableShape::getGlobalBounds().height);
	}

	int Button::getMaxNumInRow() const
	{
		int numColumns;
		if (InteractableShape::getPointCount() == 4) // for a rectangle
		{
			if (getPrimaryDim() > ButtonSizes::RECT_SM_W / 2.)
			{
				numColumns = 1;
			}
			else
			{
				numColumns = 2;
			}
		}
		else // for a circle
		{
			if (getPrimaryDim() > ButtonSizes::CIRC_SM_R)
			{
				numColumns = 2;
			}
			else
			{
				numColumns = 3;
			}
		}
		return numColumns;
	}

	// first column has index=0
	int Button::getPositionInRow() const { return m_positionInRow; }

	// first column has index=0
	void Button::setPositionInRow(const int num) { m_positionInRow = num; }

}


