#include "Path.h"

#include "Util\Random.h"
#include "Util\Math.h"
#include <cmath>
#include <iostream>
#include <string>

Path::Path()
{
	m_sprite.setTexture(ResourceHolder::get().textures.get("grass"));
	m_sprite.setTextureRect({ 0, 0, 32, 32});
	m_width = 16.;
}

void Path::createRandomPath(int numInternalVertices)
{
	// define "isVertexOnPath" function
	// make it so that if numInternalVertices is even, the path leaves on the same side as it came in. if is odd, path leaves on other side.

	m_numVertices = numInternalVertices;
	static Random<> rand;

	m_vertices.clear();
	m_vertices.push_back(m_firstVertex);

	enum class varToHold { x_, y_, other };
	varToHold varToHold;

	if		(m_firstVertex.x == 0)	{ varToHold = varToHold::y_; }
	else if	(m_firstVertex.y == 0)	{ varToHold = varToHold::x_; }
	else							{ varToHold = varToHold::other; }	

	/*
	int randomCoord;
	for (int v = 0; v < m_numVertices; v++)
	{
		if (v != m_numVertices - 1)
		{
			randomCoord = rand.getIntInRange(64, 640);
			while ((abs(m_vertices.at(v).y - randomCoord) < 48 && varToHold == varToHold::x_)
				|| ((abs(m_vertices.at(v).x - randomCoord) < 48 && varToHold == varToHold::y_)))
			{
				randomCoord = rand.getIntInRange(64, 640);
			}

			switch (varToHold)
			{
			case(varToHold::x_):
				m_vertices.push_back({ (float)m_vertices.at(v).x, (float)randomCoord });
				varToHold = varToHold::y_;
				break;

			case(varToHold::y_):
				m_vertices.push_back({ (float)randomCoord, (float)m_vertices.at(v).y });
				varToHold = varToHold::x_;
				break;

			default:
				break;
			}
		}
		else
		{ // placing the (second)-last vertex, so must align path with m_lastVertex
			if (m_lastVertex.x == 0)
			{
				if (abs(m_vertices.back().y - m_lastVertex.y) < 48)
				{
					if (m_vertices.back().y > m_lastVertex.y) { m_lastVertex.y -= 48; }
					else { m_lastVertex.y = m_lastVertex.y += 48; }
				}
				m_vertices.push_back({ m_vertices.back().x, m_lastVertex.y });
			}
			else if (m_lastVertex.y == 0)
			{
				if (abs(m_vertices.back().x - m_lastVertex.x) < 48)
				{
					if (m_vertices.back().x > m_lastVertex.x) { m_lastVertex.x -= 48; }
					else { m_lastVertex.x += 48; }
				}
				m_vertices.push_back({ m_lastVertex.x, m_vertices.back().y });
			}

			m_vertices.push_back(m_lastVertex);
		}
	}*/

	int randX;
	int randY;
	for (int v = 0; v < m_numVertices; v++)
	{
		if (v != m_numVertices - 1)
		{
			randX = rand.getIntInRange(64, 640);
			randY = rand.getIntInRange(64, 640);
			m_vertices.push_back(sf::Vector2f((float)randX, (float)randY));
		}
		else if (v == m_numVertices - 1)
		{
			m_vertices.push_back(m_lastVertex);
		}
	}

	generateSpritePath();

	std::cout << "The randomly-generated list of vertices is: " << std::endl;
	for (unsigned int counter = 0; counter < m_vertices.size(); counter++)
	{
		std::cout << std::to_string(m_vertices.at(counter).x) + ", " + std::to_string(m_vertices.at(counter).y) << std::endl;
	}

}

void Path::createCustomPath(std::vector<sf::Vector2f>& vertices)
{
	m_vertices.clear();
	
	m_vertices.push_back(m_firstVertex);

	for (unsigned int v = 0; v < vertices.size(); v++)
	{
		m_vertices.push_back(vertices.at(v));
	}

	m_vertices.push_back(m_lastVertex);

	generateSpritePath();
}

bool Path::isVertexOnPath(sf::Vector2f& vertex)
{
	return false;
}

std::vector<sf::Vector2f>& Path::getVertices()
{
	return m_vertices;
}

float Path::getLength()
{
	m_pathLength = 0;

	for (unsigned int i = 1; i < m_vertices.size(); i++)
	{
		m_pathLength = m_pathLength
			+ sqrtf((m_vertices.at(i).x - m_vertices.at(i - 1).x) * (m_vertices.at(i).x - m_vertices.at(i - 1).x)
			+ (m_vertices.at(i).y - m_vertices.at(i - 1).y) * (m_vertices.at(i).y - m_vertices.at(i - 1).y));
	}

	std::cout << "PATH LENGTH IS: " << std::to_string(m_pathLength) << std::endl;
	return m_pathLength;
}

void Path::setWidth(float width)
{
	m_width = width;
}

float Path::getWidth() const
{
	return m_width;
}

void Path::generateSpritePath()
{
	/*
	int dy = m_sprite.getTextureRect().height;
	int dx = m_sprite.getTextureRect().width;
	
	//sf::Sprite& firstSprite(m_sprite);
	//firstSprite.setPosition(m_vertices.at(0));
	//m_spritePath.push_back(firstSprite);

	float pos;
	for (unsigned int v = 1; v < m_vertices.size(); v++)
	{
		if (m_vertices.at(v).x == m_vertices.at(v - 1).x && m_vertices.at(v).y > m_vertices.at(v-1).y)
		{
			pos = m_vertices.at(v - 1).y;

			while (pos < m_vertices.at(v).y)
			{
				sf::Sprite& sprite(m_sprite);

				sprite.setPosition(m_vertices.at(v).x, pos);
				m_spritePath.push_back(sprite);

				pos = pos + dy;
			}
		}
		else if (m_vertices.at(v).x == m_vertices.at(v - 1).x && m_vertices.at(v).y < m_vertices.at(v - 1).y)
		{
			pos = m_vertices.at(v - 1).y;

			while (pos > m_vertices.at(v).y)
			{
				sf::Sprite& sprite(m_sprite);

				sprite.setPosition(m_vertices.at(v).x, pos);
				m_spritePath.push_back(sprite);

				pos = pos - dy;
			}
		}
		else if (m_vertices.at(v).y == m_vertices.at(v - 1).y && m_vertices.at(v).x > m_vertices.at(v - 1).x)
		{
			pos = m_vertices.at(v - 1).x;

			while (pos < m_vertices.at(v).x)
			{
				sf::Sprite& sprite(m_sprite);

				sprite.setPosition(pos, m_vertices.at(v).y);
				m_spritePath.push_back(sprite);

				pos = pos + dx;
			}
		}
		else if (m_vertices.at(v).y == m_vertices.at(v - 1).y && m_vertices.at(v).x < m_vertices.at(v - 1).x)
		{
			pos = m_vertices.at(v - 1).x;

			while (pos > m_vertices.at(v).x)
			{
				sf::Sprite& sprite(m_sprite);

				sprite.setPosition(pos, m_vertices.at(v).y);
				m_spritePath.push_back(sprite);

				pos = pos - dx;
			}
		}
	}*/
	for (unsigned int v = 1; v < m_vertices.size(); v++)
	{
		//sf::Sprite rectangle;
		sf::RectangleShape rectangle;

		rectangle.setTexture(&ResourceHolder::get().textures.get("grass_circle"));
		
		/*rectangle.setTextureRect(sf::IntRect(0, 0, sqrtf((m_vertices.at(v).x - m_vertices.at(v - 1).x) * (m_vertices.at(v).x - m_vertices.at(v - 1).x)
			+ (m_vertices.at(v).y - m_vertices.at(v - 1).y) * (m_vertices.at(v).y - m_vertices.at(v - 1).y)) + 2 * tol, 2 * tol));*/

		rectangle.setSize(sf::Vector2f(sqrtf((m_vertices.at(v).x - m_vertices.at(v - 1).x) * (m_vertices.at(v).x - m_vertices.at(v - 1).x)
			+ (m_vertices.at(v).y - m_vertices.at(v - 1).y) * (m_vertices.at(v).y - m_vertices.at(v - 1).y)) + 2 * m_width, 2 * m_width));

		rectangle.setOrigin(m_width, m_width);

		rectangle.setPosition(m_vertices.at(v - 1).x, m_vertices.at(v - 1).y);

		rectangle.setRotation(toDegrees(atan2f(m_vertices.at(v).y - m_vertices.at(v - 1).y, m_vertices.at(v).x - m_vertices.at(v - 1).x)));

		m_rectPath.push_back(rectangle);
	}



}



void Path::update()
{

}

void Path::render(sf::RenderTarget& renderer)
{
	/*
	for (auto& sprite : m_spritePath)
	{
		renderer.draw(sprite);
	}*/

	
	for (auto& rect : m_rectPath)
	{
		renderer.draw(rect);
	}
}