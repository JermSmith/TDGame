#include "GameObject.h"
#include "Util\Math.h"

#include <iostream>


const sf::Vector2f& GameObject::getPosition() const { return m_position; }

void GameObject::setPosition(sf::Vector2f& position) { m_position = position; }


const sf::Vector2f& GameObject::getSize() const { return m_size; }

void GameObject::setSize(sf::Vector2f& size) { m_size = size; }


bool GameObject::interferesWithPath(Path& path)
{
	float t_ = path.getWidth() / 2; // t_ is half width

	// lines directly below assume m_position takes top-left corner of object, and object is aligned with axes
	std::vector<sf::Vector2f> corners = {};
	//corners.push_back(m_position); // top left
	//corners.push_back(sf::Vector2f(m_position.x + m_size.x, m_position.y)); // top right
	//corners.push_back(sf::Vector2f(m_position.x, m_position.y + m_size.y)); // bottom left
	//corners.push_back(sf::Vector2f(m_position.x + m_size.x, m_position.y + m_size.y)); // bottom right
	corners.push_back(sf::Vector2f(m_position.x + m_size.x / 2, m_position.y + m_size.y / 2)); // centre

	corners.push_back(sf::Vector2f(m_position.x + (m_size.x - sqrtf(2)) / 2, m_position.y + (m_size.y - sqrtf(2)) / 2)); // top left of circle
	corners.push_back(sf::Vector2f(m_position.x + (m_size.x + sqrtf(2)) / 2, m_position.y + (m_size.y - sqrtf(2)) / 2)); // top right of circle
	corners.push_back(sf::Vector2f(m_position.x + (m_size.x - sqrtf(2)) / 2, m_position.y + (m_size.y + sqrtf(2)) / 2)); // bottom left of circle
	corners.push_back(sf::Vector2f(m_position.x + (m_size.x + sqrtf(2)) / 2, m_position.y + (m_size.y + sqrtf(2)) / 2)); // bottom right of circle

	corners.push_back(sf::Vector2f(m_position.x + m_size.x / 2, m_position.y)); // top middle
	corners.push_back(sf::Vector2f(m_position.x, m_position.y + m_size.y / 2)); // left middle
	corners.push_back(sf::Vector2f(m_position.x + m_size.x, m_position.y + m_size.y / 2)); // right middle
	corners.push_back(sf::Vector2f(m_position.x + m_size.x / 2, m_position.y + m_size.y)); // bottom middle

	// should specify different "corners" for a circle, diamond, etc.

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

		float m_; // slope of path segment ("down-right" is positive, "up-right" is negative)

		for (sf::Vector2f& corner : corners)
		{
			// check vertex interference

			if (i != path.getVertices().size() - 1) // NOT last vertex
			{
				if (distanceBetweenPoints(corner.x, corner.y, vo.x, vo.y) <= path.getVertexWidth() / sqrtf(2))
				{
					return true; // a "corner" interferes with a vertex
				}
			}
			else // 
			{
				if (distanceBetweenPoints(corner.x, corner.y, vo.x, vo.y) <= path.getVertexWidth() / sqrtf(2))
				{
					return true; // a "corner" interferes with second-last vertex
				}
				if (distanceBetweenPoints(corner.x, corner.y, vi.x, vi.y) <= path.getVertexWidth() / sqrtf(2))
				{
					return true; // a "corner" interferes with last vertex
				}
			}

			// check straight section interference

			if (theta == 0 || theta == PI || theta == -PI)
			{
				if (cos(theta) * corner.y >= cos(theta) * ol.y &&
					cos(theta) * corner.y <= cos(theta) * ir.y &&
					cos(theta) * corner.x >= cos(theta) * ol.x &&
					cos(theta) * corner.x <= cos(theta) * ir.x)
				{
					return true; // a "corner" is inside the path space
				}
			}

			else if (theta == PI / 2 || theta == -PI / 2)
			{
				if (sin(theta) * corner.y >= sin(theta) * ol.y &&
					sin(theta) * corner.y <= sin(theta) * ir.y &&
					sin(theta) * corner.x <= sin(theta) * ol.x &&
					sin(theta) * corner.x >= sin(theta) * ir.x)
				{
					return true; // a "corner" is inside the path space
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
					return true; // a "corner" is inside the path space
				}
			}
		}
	}

	return false;
}