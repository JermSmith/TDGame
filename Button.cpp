#include "Button.h"
#include "Util\Math.h"
#include <iostream>

namespace gui
{
	Button::Button(ButtonSize size)
	{
		m_buttonSize = size;

		m_button.setOutlineThickness(-2);
		m_button.setOutlineColor(sf::Color::Green);
		m_button.setFillColor(sf::Color::Black);

		float radius;
		float theta;
		switch (m_buttonSize)
		{
		case ButtonSize::Wide:
			m_button.setPointCount(4);
			m_button.setPoint(0, sf::Vector2f(-128, -24)); // top left
			m_button.setPoint(1, sf::Vector2f(128, -24)); // top right
			m_button.setPoint(2, sf::Vector2f(128, 24)); // bottom right
			m_button.setPoint(3, sf::Vector2f(-128, 24)); // bottom left
			break;

		case ButtonSize::Small:
			m_button.setPointCount(4);
			m_button.setPoint(0, sf::Vector2f(-(float)sizes::PLAYINGMENU_X / 4, -24)); // top left
			m_button.setPoint(1, sf::Vector2f((float)sizes::PLAYINGMENU_X / 4, -24)); // top right
			m_button.setPoint(2, sf::Vector2f((float)sizes::PLAYINGMENU_X / 4, 24)); // bottom right
			m_button.setPoint(3, sf::Vector2f(-(float)sizes::PLAYINGMENU_X / 4, 24)); // bottom left
			break;

		case ButtonSize::Circle2:
			m_button.setPointCount(50);
			radius = 20;
			theta = 0; // angle in radians
			for (int p = 0; p < (signed)m_button.getPointCount(); p++)
			{
				float x = radius * cosf(theta);
				float y = radius * sinf(theta);

				m_button.setPoint(p, sf::Vector2f(x, y));

				theta = theta + 2 * PI / m_button.getPointCount(); // incrementing the angle getPointCount times makes one revolution
			}
			break;

		case ButtonSize::Circle3:
			// the origin of the circle is (0, 0) by default,
			// which is the centre of the circle, since we place all points a distance "radius" away from (0, 0)

			m_button.setPointCount(50);

			radius = 32;
			theta = 0; // angle in radians
			for (int p = 0; p < (signed)m_button.getPointCount(); p++)
			{
				float x = radius * cosf(theta);
				float y = radius * sinf(theta);

				m_button.setPoint(p, sf::Vector2f(x, y));

				theta = theta + 2 * PI / m_button.getPointCount(); // incrementing the angle getPointCount times makes one revolution
			}
			break;
		}
	}

	void Button::setFunction(std::function<void(void)> func)
	{
		m_function = func;
	}

	void Button::setText(const std::string& str)
	{
		m_text.setString(str);
	}

	void Button::setTexture(const sf::Texture& tex)
	{
		m_button.setTexture(&tex);
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
				if (m_buttonSize == ButtonSize::Circle3) // is a circle
				{
					if (distanceBetweenPoints(m_button.getPosition(), pos) <
						m_button.getGlobalBounds().width / 2) // if distance is less than radius
					{
						m_function();
					}
				}
				else // is a rectangle
				{
					if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y))
						//global bounds conform exactly to the rectangle b/c there is no rotation applied to the rectangle
					{
						m_function();
					}
				}

			default:
				break;
			}

		default:
			break;
		}
	}

	void Button::render(sf::RenderTarget& renderer)
	{
		renderer.draw(m_button);
		renderer.draw(m_text);
	}

	void Button::setPosition(const sf::Vector2f& pos)
	{
		m_position = pos;

		m_button.setPosition(m_position);

		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 1.25f);
		m_text.setPosition(m_position);
	}

	//sf::Vector2f Button::getPosition() { return m_position; }

	sf::Vector2f Button::getSize() const
	{
		return sf::Vector2f(m_button.getGlobalBounds().width, m_button.getGlobalBounds().height);
	}

	int Button::getMaxNumInRow() const
	{
		int numColumns = 1;
		switch (m_buttonSize)
		{
		case ButtonSize::Wide:
			numColumns = 1;
			break;
		case ButtonSize::Small:
			numColumns = 2;
			break;
		case ButtonSize::Circle2:
			numColumns = 2;
			break;
		case ButtonSize::Circle3:
			numColumns = 3;
			break;
		}
		return numColumns;
	}

	// first column has index=0
	int Button::getPositionInRow() const
	{
		return m_positionInRow;
	}

	// first column has index=0
	void Button::setPositionInRow(const int num)
	{
		m_positionInRow = num;
	}

	// private methods below this line

	//void Button::updateText()
	//{
		//m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 1.25f); // origin is slightly above the centre point
	//}

}

