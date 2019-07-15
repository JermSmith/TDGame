#include "Tower.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"
#include <algorithm>

Tower::Tower()
{

}

Tower::Tower(const sf::RenderWindow& window)
{
	m_size = sf::Vector2f(64, 64);
	/*m_position = sf::Vector2f(sf::Mouse::getPosition(window).x * (float)OG_WINDOW_SIZE_X / window.getSize().x
		, sf::Mouse::getPosition(window).y * (float)OG_WINDOW_SIZE_Y / window.getSize().y);
	//position where the mouse is clicked; want this to be centre of circle*/
	m_position = sf::Vector2f(sf::Mouse::getPosition(window));
	//position where the mouse is clicked; want this to be centre of circle

	m_circle.setRadius(m_size.x / 2);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	//origin is relative to the top left corner of the circle's surrounding "box"; in this case, set to be the centre of circle
	m_circle.setPosition(sf::Vector2f(m_position.x, m_position.y)); //origin of the circle goes to this position, which is location of click
	m_circle.setFillColor(sf::Color::Cyan);
}

// (1)window, (2)attack type, (3)strength, (4)range, (5)rate[in ms]
Tower::Tower(const sf::RenderWindow& window, attackType type, int strength, int range, int rate)
{
	m_size = sf::Vector2f(64, 64);
	m_position = sf::Vector2f(sf::Mouse::getPosition(window));
	//position where the mouse is clicked; want this to be centre of circle

	// m_strengthString.setFontResourceHolder::get().fonts.get("stkaiti"));
	m_strengthString.setFont(ResourceHolder::get().fonts.get("arial"));
	m_strengthString.setPosition(m_position);
	m_strengthString.setFillColor(sf::Color::Red);

	m_circle.setRadius(m_size.x / 2);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	//origin is relative to the top left corner of the circle's surrounding "box"; in this case, set to be the centre of circle
	m_circle.setPosition(sf::Vector2f(m_position.x, m_position.y)); //origin of the circle goes to this position, which is location of click
	m_circle.setFillColor(sf::Color::Cyan);

	m_attackType = type;

	switch (m_attackType)
	{
	case attackType::divide:
	{
		m_strength = strength;
		m_strengthString.setString("/ " + std::to_string(m_strength));
		break;
	}
	case attackType::subtract:
	{
		m_strength = strength;
		m_strengthString.setString("- " + std::to_string(m_strength));
		break;
	}
	case attackType::squareroot:
	{
		m_strength = 1; //meaningless
		m_strengthString.setString("Sqrt");
		break;
	}
	case attackType::cuberoot:
	{
		m_strength = 1; //meaningless
		m_strengthString.setString("Cbrt");
		break;
	}
	default:
	{

		break;
	}
	}

	m_range = range;
	m_rate = rate;
}


void Tower::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	switch (e.type)
	{
	case sf::Event::EventType::MouseButtonReleased:
		break;

	default:
		break;
	}
}

void Tower::update(std::vector<std::unique_ptr<Enemy>>& enemies)
{
	m_delayTime = sf::milliseconds(m_rate);
	m_elapsedTime = m_timer.getElapsedTime() - m_timePoint;

	if (m_elapsedTime > m_delayTime)
	{
		m_timePoint = m_timer.getElapsedTime();

		this->reduceEnemyHealth(enemies);
	}
}

void Tower::reduceEnemyHealth(std::vector<std::unique_ptr<Enemy>>& enemies)
{
	float distance;
	float minDistance = (float)this->getRange(); //reset
	int enemyIndex = -1;

	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		distance = distanceBetweenPoints(
			enemies.at(i)->getPosition().x, enemies.at(i)->getPosition().y, this->getPosition().x, this->getPosition().y);

		if (distance <= this->getRange())
		{
			if (distance <= minDistance)
			{
				switch (m_attackType) // only doing these calculations for enemies in range
				{
				case attackType::divide:
					if (enemies.at(i)->getHealth() % this->m_strength == 0) // mod
					{
						minDistance = distance; //new minimum distance found
						enemyIndex = i;
					}
					break;
				case attackType::subtract:
					minDistance = distance; // new minumum distance found
					enemyIndex = i;
					break;
				case attackType::squareroot:
					if (std::round(std::sqrt(enemies.at(i)->getHealth())) - std::sqrt(enemies.at(i)->getHealth()) == 0) // is a perfect square
					{
						minDistance = distance; // new minumum distance found
						enemyIndex = i;
					}
					break;
				case attackType::cuberoot:
					if (std::round(std::cbrt(enemies.at(i)->getHealth())) - std::cbrt(enemies.at(i)->getHealth()) == 0) // is a perfect square
					{
						minDistance = distance; // new minumum distance found
						enemyIndex = i;
					}
					break;
				default:
					break;
				}
			}
		}
	}
	if (enemyIndex != -1) //changed
	{
		switch (m_attackType)
		{
		case attackType::divide:
			enemies.at(enemyIndex)->setHealth(enemies.at(enemyIndex)->getHealth() / m_strength);
			break;
		case attackType::subtract:
			enemies.at(enemyIndex)->setHealth(enemies.at(enemyIndex)->getHealth() - m_strength);
			break;
		case attackType::squareroot:
			enemies.at(enemyIndex)->setHealth((int)std::sqrt(enemies.at(enemyIndex)->getHealth()));
			break;
		case attackType::cuberoot:
			enemies.at(enemyIndex)->setHealth((int)std::cbrt(enemies.at(enemyIndex)->getHealth()));
			break;
		default:
			break;
		}
	}
}

void Tower::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_circle);
	renderer.draw(m_strengthString);
}

int Tower::getRange() { return m_range; }
void Tower::setRange(int range) { m_range = range; }

int Tower::getStrength() { return m_strength; }
void Tower::setStrength(int strength) { m_strength = strength; }


bool Tower::bInterferesWithScene(std::vector<std::unique_ptr<Tower>>& towers, Path & path, const sf::RenderWindow & window)
{
	float t_ = path.getWidth() / 2; // t_ is half width

	std::vector<sf::Vector2f> corners = {}; // vector containing all points to check for potential collision

	// the following assignment assumes m_position takes centre of circle (and that circle is aligned with axes, although doesn't matter for circles)
	corners.push_back(m_position); // centre

	int numOfPointsOnCircle = 16; // number of points on circle to check for possible collisions; power of 2 allows top and bottom of circle to be included
	for (int angle = (-numOfPointsOnCircle / 2 + 1); angle <= numOfPointsOnCircle; angle++)
	{
		corners.push_back(sf::Vector2f(
			m_position.x + cos(angle * PI * 2 / numOfPointsOnCircle) * (m_size.x / 2),
			m_position.y + sin(angle * PI * 2 / numOfPointsOnCircle) * (m_size.y / 2))); // e.g. for increments of PI/4, # of divisions is 8
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

	// above here is checking for interference between newObj and path
	// below here is checking for interference between newObj and other objects, assuming all objects are circles (size.x = size.y for circles)

	for (std::unique_ptr<Tower>& tower : towers)
	{
		if (distanceBetweenPoints(m_position.x, m_position.y, tower->getPosition().x, tower->getPosition().y) <
			(m_size.x / 2 + tower->getSize().x / 2))
		{
			return true;
		}
	}

	// below here is checking for interference with menu

	if ((unsigned)sf::Mouse::getPosition(window).x > window.getSize().x - (200 + 150 + 32))
		// this is 200 for x-distance of centre of menu from right side of screen + 150 for half of width of menu + 32 for 1/2 tower radius
	{
		return true;
	}

	return false;
}

