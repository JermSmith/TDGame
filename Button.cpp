#include "Button.h"
#include "Util\Math.h"
#include <iostream>
//#include "Util\ColourManager.h"

namespace gui
{
	Button::Button(float radius, int numPts)
		: InteractableShape(radius, numPts) // this line calls InteractableShape constructor
	{
		InteractableShape::setOutlineThickness(-2);
		InteractableShape::setOutlineColour(sf::Color::Green);
		InteractableShape::setFillColour(sf::Color::Black);
	}

	Button::Button(float width, float height)
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
				if (isRolledOn(window)) // checks if the button is rolled on
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

	sf::Vector2f Button::getSize() const // TODO: make this function return closer fit for other polygons
	{
		return sf::Vector2f(InteractableShape::getGlobalBounds().width
			, InteractableShape::getGlobalBounds().height);
	}

	int Button::getMaxNumInRow() const
	{
		int numColumns;

		if (InteractableShape::bIsRegularPolygon())
		{
			numColumns = 3;
		}
		else if (InteractableShape::getPrimaryDim() > ButtonSizes::RECT_SM_W / 2.) // long rectangle
		{
			numColumns = 1;
		}
		else // shorter rectangle
		{
			numColumns = 2;
		}

		return numColumns;
	}

	// first column has index=0
	int Button::getPositionInRow() const { return m_positionInRow; }

	// first column has index=0
	void Button::setPositionInRow(const int num) { m_positionInRow = num; }

}




