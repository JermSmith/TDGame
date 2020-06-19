#include "InteractableShape.h"
#include "Util\Math.h"

InteractableShape::InteractableShape(const float& radius, const int& pointCount)
{
	defineShape(radius, pointCount);
}

InteractableShape::InteractableShape(const float& width, const float& height)
{
	defineShape(width, height);
}

void InteractableShape::defineShape(const float& radius, const int& pointCount)
{
	m_shape.setPointCount(pointCount);
	float theta;
	switch (pointCount)
	{
	case 3: { theta = -PI / 2.; break; } // angle in radians
	case 4: { theta = -PI / 4.; break; }
	case 5: { theta = -PI / 2.; break; }
	case 6: { theta = -PI / 2.; break; }
	case 7: { theta = -PI / 2.; break; }
	case 8: { theta = -PI / 8.; break; }
	case 9: { theta = -PI / 2.; break; }
	default: { theta = 0.; break; }
	}

	for (int p = 0; p < (signed)m_shape.getPointCount(); p++)
	{
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		m_shape.setPoint(p, sf::Vector2f(x, y));

		theta = theta + 2 * PI / m_shape.getPointCount(); // incrementing theta "getPointCount" times makes one revolution
	}
}

void InteractableShape::defineShape(const float& width, const float& height)
{
	m_shape.setPointCount(4);
	m_shape.setPoint(0, sf::Vector2f(width / 2.f, -height / 2.f)); // top right
	m_shape.setPoint(1, sf::Vector2f(-width / 2.f, -height / 2.f)); // top left
	m_shape.setPoint(2, sf::Vector2f(-width / 2.f, height / 2.f)); // bottom left
	m_shape.setPoint(3, sf::Vector2f(width / 2.f, height / 2.f)); // bottom right
}

int InteractableShape::getPointCount() const
{
	return m_shape.getPointCount();
}

bool InteractableShape::isRolledOn(const sf::RenderWindow& window) const
{
	auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (bIsRegularPolygon()) // regular polygon
	{
		return (distanceBetweenPoints(pos, m_shape.getPosition()) < getPrimaryDim());
	}
	else // for a rectangle
	{
		return m_shape.getGlobalBounds().contains((float)pos.x, (float)pos.y);
	}
}

void InteractableShape::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_shape); // TODO: make this render function const
}

float InteractableShape::getPrimaryDim() const
{
	if (bIsRegularPolygon()) // for a regular polygon
	{
		return distanceBetweenPoints(m_shape.getOrigin(), m_shape.getPoint(0)); // from centre to a point
	}
	else// if (m_shape.getPointCount() == 4)
	{
		return distanceBetweenPoints(m_shape.getPoint(0), m_shape.getPoint(1)) / 2; // half of width of rectangle
	}
	//else
	//{
		//throw "Cannot compute InteractableShape::getPrimaryDim(). InteractableShape is made up of fewer than 4 points.";
	//}
}

sf::FloatRect InteractableShape::getGlobalBounds() const
{
	return m_shape.getGlobalBounds();
}

void InteractableShape::setOrigin(const sf::Vector2f& origin)
{
	m_shape.setOrigin(origin);
}

void InteractableShape::setPosition(const sf::Vector2f& position)
{
	m_shape.setPosition(position);
}

sf::Color InteractableShape::getFillColour() const
{
	return m_shape.getFillColor();
}

void InteractableShape::setFillColour(const sf::Color& colour)
{
	if (m_shape.getFillColor() == sf::Color(-1, -1, -1)) // initialized in InteractableShape.h
	{
		m_originalFillColour = colour; // sets the original fill colour, since it has not been set yet
	}
	m_shape.setFillColor(colour);
}

void InteractableShape::setRolledAppearance()
{
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setOutlineThickness(-2);
}

void InteractableShape::removeRolledAppearance()
{
	m_shape.setOutlineThickness(0);
}

void InteractableShape::setClickedAppearance()
{
	m_shape.setFillColor(sf::Color(100, 100, 100));
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setOutlineThickness(-1);
}

void InteractableShape::removeClickedAppearance()
{
	m_shape.setFillColor(m_originalFillColour);
	m_shape.setOutlineThickness(0);
}

void InteractableShape::setOutlineThickness(const float& thickness)
{
	m_shape.setOutlineThickness(thickness);
}

void InteractableShape::setOutlineColour(const sf::Color& colour)
{
	m_shape.setOutlineColor(colour);
}

void InteractableShape::setTexture(const sf::Texture& tex)
{
	m_shape.setTexture(&tex);
}

bool InteractableShape::bIsRegularPolygon() const
{
	bool b;
	if ((m_shape.getGlobalBounds().width / m_shape.getGlobalBounds().height > 1.2f) ||
		(m_shape.getGlobalBounds().width / m_shape.getGlobalBounds().height < 0.8f)) // more rectangular than square
	{
		b = false;
	}
	else
	{
		b = true;
	}
	return b;
}




