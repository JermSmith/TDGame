#include "Button.h"
#include "Util\Math.h"
#include <iostream>
//#include "Util\ColourManager.h"

namespace gui
{
	CircularButton::CircularButton(ButtonSize size)
	{
		m_buttonSize = size;

		m_button.setOutlineThickness(-2);
		m_button.setOutlineColor(sf::Color::Green);
		m_button.setFillColor(sf::Color::Black);

		float radius;
		float theta;
		switch (m_buttonSize)
		{
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

	bool CircularButton::isRolledOn(const sf::RenderWindow& window) const
	{
		auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		return distanceBetweenPoints(pos, m_button.getPosition()) < getSize().x / 2.f;
	}

	void CircularButton::handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		switch (e.type)
		{
		case sf::Event::MouseButtonPressed:
			switch (e.mouseButton.button)
			{
			case sf::Mouse::Left:
				if (distanceBetweenPoints(m_button.getPosition(), pos) <
					m_button.getGlobalBounds().width / 2) // if distance is less than radius
				{
					m_function();
				}
				break;
			default:
				break;
			}
			break;

		case sf::Event::MouseMoved:
			if (isRolledOn(window))
			{
				m_button.setFillColor(sf::Color(51, 51, 51));
			}
			else
			{
				m_button.setFillColor(sf::Color::Black);
			}
			break;

		default:
			break;
		}
	}

	void CircularButton::render(sf::RenderTarget& renderer)
	{
		renderer.draw(m_button);
		renderer.draw(m_text);
	}

	void CircularButton::setPosition(const sf::Vector2f& pos)
	{
		m_position = pos;

		m_button.setPosition(m_position);

		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 1.25f);
		m_text.setPosition(m_position);
	}

	//sf::Vector2f Button::getPosition() { return m_position; }

	sf::Vector2f CircularButton::getSize() const
	{
		return sf::Vector2f(m_button.getGlobalBounds().width, m_button.getGlobalBounds().height);
	}

	int CircularButton::getMaxNumInRow() const
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
	int CircularButton::getPositionInRow() const { return m_positionInRow; }

	// first column has index=0
	void CircularButton::setPositionInRow(const int num) { m_positionInRow = num; }
	
	//int CircularButton::getPositionInMenu() const { return m_positionInMenu; }
	//void CircularButton::setPositionInMenu(const int num) { m_positionInMenu = num; }

	void CircularButton::setFunction(std::function<void(void)> func) { m_function = func; }

	//void CircularButton::setText(const std::string& str) { m_text.setString(str); }

	void CircularButton::setTexture(const sf::Texture& tex) { m_button.setTexture(&tex); }




	RectangularButton::RectangularButton(ButtonSize size)
	{
		m_buttonSize = size;

		m_button.setOutlineThickness(-2);
		m_button.setOutlineColor(sf::Color::Green);
		m_button.setFillColor(sf::Color::Black);

		float radius = 0;
		float theta = 0;
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

		default:
			break;
		}

	}

	bool RectangularButton::isRolledOn(const sf::RenderWindow& window) const
	{
		auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		return m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y);
	}

	void RectangularButton::handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		switch (e.type)
		{
		case sf::Event::MouseButtonPressed:
			switch (e.mouseButton.button)
			{
			case sf::Mouse::Left:
				if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y))
					//global bounds conform exactly to the rectangle b/c there is no rotation applied to the rectangle
				{
					m_function();
				}
				break;
			default:
				break;
			}
			break;

		case sf::Event::MouseMoved:
			if (isRolledOn(window))
			{
				m_button.setFillColor(sf::Color(51, 51, 51));
			}
			else
			{
				m_button.setFillColor(sf::Color::Black);
			}
			break;

		default:
			break;
		}
	}

	void RectangularButton::render(sf::RenderTarget& renderer)
	{
		renderer.draw(m_button);
		renderer.draw(m_text);
	}

	void RectangularButton::setPosition(const sf::Vector2f& pos)
	{
		m_position = pos;

		m_button.setPosition(m_position);

		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 1.25f);
		m_text.setPosition(m_position);
	}

	sf::Vector2f RectangularButton::getSize() const
	{
		return sf::Vector2f(m_button.getGlobalBounds().width, m_button.getGlobalBounds().height);
	}

	int RectangularButton::getMaxNumInRow() const
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
	int RectangularButton::getPositionInRow() const { return m_positionInRow; }

	// first column has index=0
	void RectangularButton::setPositionInRow(const int num) { m_positionInRow = num; }

	//int RectangularButton::getPositionInMenu() const { return m_positionInMenu; }
	//void RectangularButton::setPositionInMenu(const int num) { m_positionInMenu = num; }

	void RectangularButton::setFunction(std::function<void(void)> func) { m_function = func; }

	//void RectangularButton::setText(const std::string& str) { m_text.setString(str); }

	void RectangularButton::setTexture(const sf::Texture& tex) { m_button.setTexture(&tex); }





}



