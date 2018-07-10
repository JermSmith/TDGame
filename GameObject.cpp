#include "GameObject.h"
#include <iostream>


const sf::Vector2f& GameObject::getPosition() const { return m_position; }

const sf::Vector2f& GameObject::getSize() const { return m_size; }
		

void GameObject::setPosition(sf::Vector2f& position) { m_position = position; }

void GameObject::setSize(sf::Vector2f& size) { m_size = size; }


bool GameObject::interferesWithPath(Path& path)
{
	// if this function is either computationally expensive or its data can be stored in a relatively simple structure, then
	// consider storing some of this information in the path object. but would need to ensure this data is stored and that it
	// is stored in a function/process that makes sense, not hidden away in another procedure
	float t_ = path.getWidth();

	// lines directly below assume m_position takes top-left corner of object, and object is aligned with axes
	std::vector<sf::Vector2f> corners = {};
	corners.push_back(m_position);
	corners.push_back(sf::Vector2f(m_position.x + m_size.x, m_position.y));
	corners.push_back(sf::Vector2f(m_position.x, m_position.y + m_size.y));
	corners.push_back(sf::Vector2f(m_position.x + m_size.x, m_position.y + m_size.y));

	for (unsigned int i = 1; i < path.getVertices().size(); i++)
	{
		sf::Vector2f vo = path.getVertices().at(i - 1);
		sf::Vector2f vi = path.getVertices().at(i);

		float theta = atan2f(vi.y - vo.y, vi.x - vo.x); // angle of path segment in radians (CW is +ve from +ve x-axis)

		// ol is back left corner of the rectangle, ir is front right corner of the rectangle
		sf::Vector2f ol = sf::Vector2f(vo.x - t_*cos(theta) + t_*sin(theta), vo.y - t_*cos(theta) - t_*sin(theta));
		sf::Vector2f or = sf::Vector2f(vo.x - t_*cos(theta) - t_*sin(theta), vo.y + t_*cos(theta) - t_*sin(theta));
		sf::Vector2f il = sf::Vector2f(vi.x + t_*cos(theta) + t_*sin(theta), vi.y - t_*cos(theta) + t_*sin(theta));
		sf::Vector2f ir = sf::Vector2f(vi.x + t_*cos(theta) - t_*sin(theta), vi.y + t_*cos(theta) + t_*sin(theta));

		float m_; // slope of path segment
		
		/*
		if (theta == 0 || theta == PI || theta == -PI)
		{
			if (cos(theta) * m_position.y >= cos(theta) * ol.y &&
				cos(theta) * m_position.y <= cos(theta) * ir.y &&
				cos(theta) * m_position.x >= cos(theta) * ol.x &&
				cos(theta) * m_position.x <= cos(theta) * ir.x)
			{
				return true; // m_position is inside the path space
			}
		}

		else if (theta == PI / 2 || theta == -PI / 2)
		{
			if (sin(theta) * m_position.y >= sin(theta) * ol.y &&
				sin(theta) * m_position.y <= sin(theta) * ir.y &&
				sin(theta) * m_position.x <= sin(theta) * ol.x &&
				sin(theta) * m_position.x >= sin(theta) * ir.x)
			{
				return true; // m_position is inside the path space
			}
		}

		else // theta != 0, pi/2, pi, -pi/2, -pi
		{
			m_ = (vi.y - vo.y) / (vi.x - vo.x); // slope of path segment

			if (cos(theta) * (m_position.y - m_*m_position.x) > cos(theta) * (ol.y - m_*ol.x) &&
				cos(theta) * (m_position.y - m_*m_position.x) < cos(theta) * (ir.y - m_*ir.x) &&
				sin(theta) * (m_position.y + (1 / m_)*m_position.x) > sin(theta) * (ol.y + (1 / m_)*ol.x) &&
				sin(theta) * (m_position.y + (1 / m_)*m_position.x) < sin(theta) * (ir.y + (1 / m_)*ir.x))
			{
				return true; // m_position is inside the path space
			}
		}*/

		for (sf::Vector2f& corner : corners)
		{
			if (theta == 0 || theta == PI || theta == -PI)
			{
				if (cos(theta) * corner.y >= cos(theta) * ol.y &&
					cos(theta) * corner.y <= cos(theta) * ir.y &&
					cos(theta) * corner.x >= cos(theta) * ol.x &&
					cos(theta) * corner.x <= cos(theta) * ir.x)
				{
					return true; // m_position is inside the path space
				}
			}

			else if (theta == PI / 2 || theta == -PI / 2)
			{
				if (sin(theta) * corner.y >= sin(theta) * ol.y &&
					sin(theta) * corner.y <= sin(theta) * ir.y &&
					sin(theta) * corner.x <= sin(theta) * ol.x &&
					sin(theta) * corner.x >= sin(theta) * ir.x)
				{
					return true; // m_position is inside the path space
				}
			}

			else // theta != 0, pi/2, pi, -pi/2, -pi
			{
				m_ = (vi.y - vo.y) / (vi.x - vo.x); // slope of path segment

				if (cos(theta) * (corner.y - m_*corner.x) > cos(theta) * (ol.y - m_*ol.x) &&
					cos(theta) * (corner.y - m_*corner.x) < cos(theta) * (ir.y - m_*ir.x) &&
					sin(theta) * (corner.y + (1 / m_)*corner.x) > sin(theta) * (ol.y + (1 / m_)*ol.x) &&
					sin(theta) * (corner.y + (1 / m_)*corner.x) < sin(theta) * (ir.y + (1 / m_)*ir.x))
				{
					return true; // m_position is inside the path space
				}
			}
		}
	}

	return false;
}