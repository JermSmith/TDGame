#include "Cursor.h"
#include "Util\Math.h"

Cursor::Cursor()
{
	
}

void Cursor::update(const sf::RenderWindow& window, const Path& path,
	const std::vector<std::unique_ptr<Tower>>& towers, bool bTowerBeingPlaced)
{
	if (bTowerBeingPlaced)
	{
		// place dummy tower at the current mouse position to check what color the cursor circle should be
		m_position = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		if (!bInterferesWithScene(towers, path))
		{
			updatePositive(); //possible to place tower here
		}
		else
		{
			updateNegative(); //not possible to place tower here
		}
	}
	else
	{
		hide(); //do not show a circle around radius, since no tower is being placed
	}
}

void Cursor::render(sf::RenderTarget& renderer)
{
	//renderer.draw(m_towerCircle);
	renderer.draw(*getCircle());
	renderer.draw(m_rangeCircle);
}

bool Cursor::bInterferesWithScene(const std::vector<std::unique_ptr<Tower>>& towers, const Path& path)
{
	// depends on tower properties m_position and m_size

	float t_ = path.getWidth() / 2; // t_ is half width

	std::vector<sf::Vector2f> corners = {}; // vector containing all points to check for potential collision

	// the following assignment assumes m_position takes centre of circle (and that circle is aligned with axes, although doesn't matter for circles)
	corners.push_back(m_position); // centre

	int numOfPointsOnCircle = 16; // number of points on circle to check for possible collisions; power of 2 allows top and bottom of circle to be included
	for (int angle = (-numOfPointsOnCircle / 2 + 1); angle <= numOfPointsOnCircle; angle++)
	{
		corners.push_back(sf::Vector2f(
			m_position.x + cos(angle * PI * 2 / numOfPointsOnCircle) * m_radius,
			m_position.y + sin(angle * PI * 2 / numOfPointsOnCircle) * m_radius)); // e.g. for increments of PI/4, # of divisions is 8
	}

	/* could specify different "corners" for a square, diamond, etc. */

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
				if (distanceBetweenPoints(corner, vo) <= path.getVertexWidth() / sqrtf(2))
				{
					return true; // a "corner" interferes with a vertex
				}
			}
			else // 
			{
				if (distanceBetweenPoints(corner, vo) <= path.getVertexWidth() / sqrtf(2))
				{
					return true; // a "corner" interferes with second-last vertex
				}
				if (distanceBetweenPoints(corner, vi) <= path.getVertexWidth() / sqrtf(2))
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

	// above here is checking for interference between newObj and path
	// below here is checking for interference between newObj and other objects, assuming all objects are circles (size.x = size.y for circles)

	for (unsigned int i = 0; i < towers.size(); i++)
	{
		if (distanceBetweenPoints(m_position, towers.at(i)->getPosition()) <
			(m_radius + towers.at(i)->getRadius()))
		{
			return true;
		}
	}

	// below here is checking for interference with menu

	if (m_position.x > sizes::WORLD_SIZE_X - (sizes::PLAYINGMENU_X + m_radius) || // menu width + 1/2 tower radius
		(m_position.x < m_radius) ||
		m_position.y < m_radius ||
		m_position.y > sizes::WORLD_SIZE_Y - m_radius)
	{
		return true;
	}

	return false;
}


// private methods below this line

void Cursor::hide()
{
	//m_towerCircle.setRadius(0);
	getCircle()->setRadius(0);
	m_rangeCircle.setRadius(0);
}

void Cursor::updatePositive()
{
	/*m_towerCircle.setRadius(m_radius);
	m_towerCircle.setOutlineThickness(-2);
	m_towerCircle.setOutlineColor(sf::Color::Cyan);
	m_towerCircle.setPosition(m_position);*/
	
	getCircle()->setRadius(m_radius);
	getCircle()->setOutlineThickness(-2);
	getCircle()->setOutlineColor(sf::Color::Cyan);
	getCircle()->setPosition(m_position);

	m_rangeCircle.setRadius(m_range);
	m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));
	m_rangeCircle.setOutlineThickness(-2);
	m_rangeCircle.setOutlineColor(sf::Color::Green);
	m_rangeCircle.setPosition(m_position);
}

void Cursor::updateNegative()
{
	/*m_towerCircle.setRadius(m_radius);
	m_towerCircle.setFillColor(sf::Color::Transparent);
	m_towerCircle.setOutlineThickness(-2);
	m_towerCircle.setOutlineColor(sf::Color::Red);
	m_towerCircle.setPosition(m_position);*/

	getCircle()->setRadius(m_radius);
	getCircle()->setFillColor(sf::Color::Transparent);
	getCircle()->setOutlineThickness(-2);
	getCircle()->setOutlineColor(sf::Color::Red);
	getCircle()->setPosition(m_position);

	m_rangeCircle.setOutlineColor(sf::Color::Transparent);
	m_rangeCircle.setFillColor(sf::Color::Transparent);
}

