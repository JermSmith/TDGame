#include "Util\Math.h"

#include "World.h"
#include "Path.h"
#include "Tower.h"
#include "Enemy.h"

World::World()
{
	m_path.createRandomPath(4);
	m_gameObjects.push_back(std::make_unique<Enemy>(m_path.getVertices(), 100)); // instantiate an enemy
}

void World::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	if (e.type == sf::Event::EventType::MouseButtonReleased && m_bTowerBeingPlaced)
	{
		//create a new object in testNewGameObject to test if it works, and if so remove it from testNewGameObject and make a new one in gameObjects
		m_testNewGameObject.push_back(std::make_unique<Tower>(window));

		if (bInterferesWithScene(m_testNewGameObject.back(), m_gameObjects, m_path, window))
		{
			m_testNewGameObject.pop_back(); //remove the new tower from the back of m_testNewGameObject since it interferes with the path
		}
		else //no interference found with new object and path, so can place object
		{
			//now that we know a new object can be placed, make a new object in gameObjects and remove the test object in testNewGameObject
			m_testNewGameObject.pop_back(); //remove the only object from testNewGameObject
			m_gameObjects.push_back(std::make_unique<Tower>(window));
			m_bTowerBeingPlaced = false;
			// will no longer check for this tower placement input until bTowerBeingPlaced is set to true again in StatePlaying.cpp by clicking on button
		}
	}
}

bool World::getBoolTowerBeingPlaced() { return m_bTowerBeingPlaced; }
void World::setBoolTowerBeingPlaced(bool b)
{
	m_bTowerBeingPlaced = b;
}

void World::handleInput()
{

}

void World::update(sf::Time deltaTime, const sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects.at(i)->update();
	}

	//Cursor.cpp should manage its own updating, not World.cpp. But cursor can't adequately check when to be updated, so World.cpp must do it for it.
	updateCursor(window);

}

//Cursor.cpp should manage its own updating, not World.cpp. But cursor can't adequately check when to be updated, so World.cpp must do it for it.
void World::updateCursor(const sf::RenderWindow& window)
{
	switch (m_bTowerBeingPlaced)
	{
	case true:
		//create a new object in testNewGameObject at the current mouse position to check what color the cursor circle should be
		m_testNewGameObject.push_back(std::make_unique<Tower>(window));

		if (bInterferesWithScene(m_testNewGameObject.back(), m_gameObjects, m_path, window))
		{
			m_cursor.updateNegative(window); //not possible to place tower here
			m_testNewGameObject.pop_back(); //remove the new tower from the back of m_testNewGameObject since color of cursor has been decided
		}
		else
		{
			m_cursor.updatePositive(window); //possible to place tower here
			m_testNewGameObject.pop_back(); //remove the new tower from the back of m_testNewGameObject since color of cursor has been decided
		}
		break;

	case false:
		m_cursor.hide(); //do not show a circle around radius, since no tower is being placed
		break;
	}
}

void World::render(sf::RenderTarget& renderer)
{
	m_path.render(renderer);

	for (const auto& obj : m_gameObjects)
	{
		obj->render(renderer);
	}

	m_cursor.render(renderer);

}

bool World::bInterferesWithScene(
	std::unique_ptr<GameObject>& newObj, std::vector<std::unique_ptr<GameObject>>& gameObjects, Path& path, const sf::RenderWindow& window)
	// checks if newObj (a gameObject) interferes with any of the objects in gameObjects, with the path, or with the right-side menu
{
	float t_ = path.getWidth() / 2; // t_ is half width

	std::vector<sf::Vector2f> corners = {}; // vector containing all points to check for potential collision

	// the following assignment assumes m_position takes centre of circle (and that circle is aligned with axes, although doesn't matter for circles)

	corners.push_back(newObj->getPosition()); // centre

	int numOfPointsOnCircle = 16; // number of points on circle to check for possible collisions; power of 2 allows top and bottom of circle to be included
	for (int angle = (-numOfPointsOnCircle / 2 + 1); angle <= numOfPointsOnCircle; angle++)
	{
		corners.push_back(sf::Vector2f(
			newObj->getPosition().x + cos(angle * PI * 2 / numOfPointsOnCircle) * (newObj->getSize().x / 2),
			newObj->getPosition().y + sin(angle * PI * 2 / numOfPointsOnCircle) * (newObj->getSize().y / 2))); // e.g. for increments of PI/4, # of divisions is 8
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

	for (std::unique_ptr<GameObject>& obj : gameObjects)
	{
		if (distanceBetweenPoints(newObj->getPosition().x, newObj->getPosition().y, obj->getPosition().x, obj->getPosition().y) <
			(newObj->getSize().x / 2 + obj->getSize().x / 2))
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

