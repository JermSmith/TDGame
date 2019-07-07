#include "Path.h"

#include "Util\Random.h" // random number generator
#include "Util\Math.h" // toDegrees in generateSprites function
#include <iostream> // getLength function
#include <string> // getLength function

Path::Path()
{
	m_firstVertex = {m_LEFT_BORDER, m_TOP_BORDER };
	m_lastVertex = { 480, m_TOP_BORDER };

	m_PATH_WIDTH = 32;
	//m_VERTEX_RADIUS = m_PATH_WIDTH * (float)1.28;
	m_STAR_WIDTH = m_PATH_WIDTH * (float)1.28; // side length of square or diamond in the star

	m_TOLERANCE = m_STAR_WIDTH + m_PATH_WIDTH;
	m_MAX_NUM_LOOPS = 20;

	m_LEFT_BORDER = m_PATH_WIDTH;
	m_TOP_BORDER = m_PATH_WIDTH;

	m_pathTexture = ResourceHolder::get().textures.get("grass");
	m_pathTexture.setRepeated(true);

	m_vertexTexture = ResourceHolder::get().textures.get("wood");
	m_vertexTexture.setRepeated(true);
}

void Path::createRandomPath(int numInternalVertices)
{
	m_numVertices = numInternalVertices;
	static Random<> rand;
	clear();
	int rand50 = rand.getIntInRange(0, 1);
	float randX;
	float randY;

	if (numInternalVertices == 0) { m_numVertices = rand.getIntInRange(3, 7); }

	// generate first vertex
	switch (rand50)
	{
	case 0:
		randX = rand.getFloatInRange(128, 720);
		m_firstVertex = sf::Vector2f(randX, m_TOP_BORDER);
		break;

	case 1:
		randY = rand.getFloatInRange(128, 640);
		m_firstVertex = sf::Vector2f(m_LEFT_BORDER, randY);
		break;

	default:
		randY = rand.getFloatInRange(128, 640);
		m_firstVertex = sf::Vector2f(m_LEFT_BORDER, randY);
		break;
	}
	m_vertices.push_back(m_firstVertex); // first vertex added

	for (int v = 1; v <= m_numVertices + 1; v++) // +1 to numVertices to account for last vertex
	{
		if (v != m_numVertices + 1) // deal with all vertices except the last vertex
		{
			int tries = 0;
			do
			{
				randX = rand.getFloatInRange(128, 720);
				randY = rand.getFloatInRange(128, 640);
				
				tries++;
				// if loops "m_MAX_NUM_LOOPS" times, then let pass
			} while (vertexInterferesWithPath(sf::Vector2f(randX, randY)) && tries < m_MAX_NUM_LOOPS);

			m_vertices.push_back(sf::Vector2f(randX, randY));
		}


		else if (v == m_numVertices + 1) // add the last vertex
		{
			int tries = 0;
			do
			{
				rand50 = rand.getIntInRange(0, 1);

				switch (rand50)
				{
				case 0:
					randX = rand.getFloatInRange(128, 720);
					m_lastVertex = sf::Vector2f(randX, m_TOP_BORDER);
					break;

				case 1:
					randY = rand.getFloatInRange(128, 640);
					m_lastVertex = sf::Vector2f(m_LEFT_BORDER, randY);
					break;

				default:
					randY = rand.getFloatInRange(128, 640);
					m_lastVertex = sf::Vector2f(m_LEFT_BORDER, randY);
					break;
				}

				tries++;
				// if loops "m_MAX_NUM_LOOPS" times, then let pass
			} while (vertexInterferesWithPath(m_lastVertex) && tries < m_MAX_NUM_LOOPS);

			m_vertices.push_back(m_lastVertex);
		}
	}
	
	generateSprites();

}

void Path::createOrthoPath(int numInternalVertices)
{
	m_numVertices = numInternalVertices;
	static Random<> rand;
	clear();
	int rand50 = rand.getIntInRange(0, 1);
	float randX;
	float randY;
	sf::Vector2f newVertex;
	
	if (numInternalVertices == 0) { m_numVertices = rand.getIntInRange(3, 7); }

	// generate first vertex
	switch (rand50)
	{
	case 0:
		randX = rand.getFloatInRange(128, 720);
		m_firstVertex = sf::Vector2f(randX, m_TOP_BORDER);
		break;

	case 1:
		randY = rand.getFloatInRange(128, 640);
		m_firstVertex = sf::Vector2f(m_LEFT_BORDER, randY);
		break;

	default:
		randY = rand.getFloatInRange(128, 640);
		m_firstVertex = sf::Vector2f(m_LEFT_BORDER, randY);
		break;
	}
	m_vertices.push_back(m_firstVertex); // first vertex added

	if (numInternalVertices == 1)
	{
		if (m_firstVertex.y == m_TOP_BORDER)
		{
			randY = rand.getFloatInRange(128, 640);
			m_vertices.push_back(sf::Vector2f(m_firstVertex.x, randY));
			m_vertices.push_back(sf::Vector2f(m_LEFT_BORDER, randY));
		}
		else if (m_firstVertex.x == m_LEFT_BORDER)
		{
			randX = rand.getFloatInRange(128, 720);
			m_vertices.push_back(sf::Vector2f(randX, m_firstVertex.y));
			m_vertices.push_back(sf::Vector2f(randX, m_TOP_BORDER));
		}

		generateSprites();
		return; // leave the function early
	}


	for (int v = 0; v <= m_numVertices - 1; v++)
	{
		if (v != m_numVertices - 1) // deal with all vertices except the last two vertices (last internal vertex, and lastVertex itself)
		{
			
			if (m_vertices.size() == 1) // only first vertex exists (happens with v=0) - add the first internal vertex
			{
				if (m_firstVertex.x == m_LEFT_BORDER)
				{
					randX = rand.getFloatInRange(128, 720);
					newVertex = sf::Vector2f(randX, m_firstVertex.y);

					m_vertices.push_back(newVertex);
				}
				else if (m_firstVertex.y == m_TOP_BORDER)
				{
					randY = rand.getFloatInRange(128, 640);
					newVertex = sf::Vector2f(m_firstVertex.x, randY);
					
					m_vertices.push_back(newVertex);
				}
			}
			
			else if (m_vertices.size() > 1) // happens with v=1 for 1st internal vertex, up to v=n-1 for (n-1)st internal vertex
			// add more internal vertices (but not last internal vertex because of wrapping if-statement)
			{
				if (m_vertices.at(v).x == m_vertices.at(v - 1).x) // last move was vertical
				{
					int tries = 0;
					do
					{
						randX = rand.getFloatInRange(128, 720);
						newVertex = sf::Vector2f(randX, m_vertices.at(v).y);
						tries++;
						// if loops "m_MAX_NUM_LOOPS" times, then let pass
					} while (vertexInterferesWithPath(newVertex) && tries < m_MAX_NUM_LOOPS);
						
					m_vertices.push_back(newVertex);
				}
				else if (m_vertices.at(v).y == m_vertices.at(v - 1).y) // last move was horizontal
				{
					int tries = 0;
					do
					{
						randY = rand.getFloatInRange(128, 640);
						newVertex = sf::Vector2f(m_vertices.at(v).x, randY);
						tries++;
						// if loops "m_MAX_NUM_LOOPS" times, then let pass
					} while (vertexInterferesWithPath(newVertex) && tries < m_MAX_NUM_LOOPS);

					m_vertices.push_back(newVertex);
				}
			}
		}

		else if (v == m_numVertices - 1) // deal with last internal vertex AND last vertex
		{
			if (m_vertices.at(v).x == m_vertices.at(v - 1).x) // last move was vertical
			{
				int tries2 = 0;
				do
				{
					// if redirected here because lastVertex interferes with path, then remove newVertex (added below)
					if (m_vertices.size() == m_numVertices + 1) // final size of m_vertices is numVertices + 2 (first + # internal + last)
					{
						m_vertices.pop_back(); // remove last element, which is newVertex
					}

					int tries1 = 0;
					do
					{
						randX = rand.getFloatInRange(128, 720);
						newVertex = sf::Vector2f(randX, m_vertices.at(v).y);
						m_lastVertex = sf::Vector2f(randX, m_TOP_BORDER);

						tries1++;
						// if loops "m_MAX_NUM_LOOPS" times, then let pass
					} while (vertexInterferesWithPath(newVertex) && tries1 < m_MAX_NUM_LOOPS);
					
					m_vertices.push_back(newVertex);
					// the interference check for lastVertex only works correctly after newVertex has been added
					tries2++;
					// if loops "m_MAX_NUM_LOOPS" times, then let pass
				} while (vertexInterferesWithPath(m_lastVertex) && tries2 < m_MAX_NUM_LOOPS);

				m_vertices.push_back(m_lastVertex);

			}
			else if (m_vertices.at(v).y == m_vertices.at(v - 1).y) // last move was horizontal
			{
				int tries2 = 0;
				do
				{
					// if redirected here because lastVertex interferes with path, then remove newVertex (added below)
					if (m_vertices.size() == m_numVertices + 1) // final size of m_vertices is numVertices + 2 (first + # internal + last)
					{
						m_vertices.pop_back(); // remove last element, which is newVertex
					}

					int tries1 = 0;
					do
					{
						randY = rand.getFloatInRange(128, 640);
						newVertex = sf::Vector2f(m_vertices.at(v).x, randY);
						m_lastVertex = sf::Vector2f(m_LEFT_BORDER, randY);

						tries1++;
						// if loops "m_MAX_NUM_LOOPS" times, then let pass
					} while (vertexInterferesWithPath(newVertex) && tries1 < m_MAX_NUM_LOOPS);

					m_vertices.push_back(newVertex);
					// the interference check for lastVertex only works correctly after newVertex has been added
					tries2++;
					// if loops "m_MAX_NUM_LOOPS" times, then let pass
				} while (vertexInterferesWithPath(m_lastVertex) && tries2 < m_MAX_NUM_LOOPS);
				
				m_vertices.push_back(m_lastVertex);
			}
		}
	}

	generateSprites();

}

void Path::createCustomPath(std::vector<sf::Vector2f>& vertices)
{
	m_vertices.clear();

	for (unsigned int v = 0; v < vertices.size(); v++)
	{
		m_vertices.push_back(vertices.at(v));
	}

	generateSprites();
}

bool Path::vertexInterferesWithPath(sf::Vector2f& vertex)
{
	float dr = 8; // resolution to check for interference
	float dx;
	float dy;
	float theta;

	sf::Vector2f p0;
	sf::Vector2f p1;
	
	/* the only differences between the two for-loops below are the assignment of p0 and p1,
		and points/vertices used to check for intersection */

	// check if new path is too close to an existing vertex
	for (unsigned int v = 1; v < m_vertices.size(); v++)
	{
		p0 = m_vertices.back(); // soon-to-be second-last vertex
		p1 = vertex; // vertex to be placed
		
		theta = atan2f(p1.y - p0.y, p1.x - p0.x);

		dx = dr * cosf(theta);
		dy = dr * sinf(theta);

		while (cosf(theta) * p0.x <= cosf(theta) * p1.x
			&& sinf(theta) * p0.y <= sinf(theta) * p1.y)
		{
			// check intersection
			//if (getDistanceBetweenPoints(p0, m_vertices.at(v-1)) <= m_TOLERANCE)
			if (distanceBetweenPoints(p0.x, p0.y, m_vertices.at(v-1).x, m_vertices.at(v-1).y) <= m_TOLERANCE)
			{
				return true; // new path segment is too close to an existing vertex
			}

			else
			{
				p0.x = p0.x + dx;
				p0.y = p0.y + dy;
			}
		}
	}

	// check if new vertex is too close to existing path
	for (unsigned int v = 1; v < m_vertices.size(); v++)
	{
		p0 = m_vertices.at(v - 1);
		p1 = m_vertices.at(v);
		
		theta = atan2f(p1.y - p0.y, p1.x - p0.x);

		dx = dr * cosf(theta);
		dy = dr * sinf(theta);

		while (cosf(theta) * p0.x <= cosf(theta) * p1.x
			&& sinf(theta) * p0.y <= sinf(theta) * p1.y)
		{
			// check intersection
			//if (getDistanceBetweenPoints(p0, vertex) <= m_TOLERANCE)
			if (distanceBetweenPoints(p0.x, p0.y, vertex.x, vertex.y) <= m_TOLERANCE)
			{
				return true; // vertex (provided in argument) is too close to an existing path
			}

			else
			{
				p0.x = p0.x + dx;
				p0.y = p0.y + dy;
			}
		}
	}

	return false;
}
/*
float Path::getDistanceBetweenPoints(sf::Vector2f& v0, sf::Vector2f& v1)
{
	return sqrtf((v1.x - v0.x) * (v1.x - v0.x) + (v1.y - v0.y) * (v1.y - v0.y));
}*/

void Path::generateSprites()
{
	sf::Sprite pathRectangle;
	pathRectangle.setTexture(m_pathTexture);
	pathRectangle.setOrigin(m_PATH_WIDTH / 2, m_PATH_WIDTH / 2);

	sf::Sprite vertexDiamond;
	vertexDiamond.setTexture(m_vertexTexture);
	vertexDiamond.setTextureRect(sf::IntRect(0, 0, (int)m_STAR_WIDTH, (int)m_STAR_WIDTH));
	vertexDiamond.setOrigin(m_STAR_WIDTH / 2, m_STAR_WIDTH / 2);
	vertexDiamond.setRotation(45);
	
	sf::Sprite vertexSquare;
	vertexSquare.setTexture(m_vertexTexture);
	vertexSquare.setTextureRect(sf::IntRect(0, 0, (int)m_STAR_WIDTH, (int)m_STAR_WIDTH));
	vertexSquare.setOrigin(m_STAR_WIDTH / 2, m_STAR_WIDTH / 2);

	/*
	sf::CircleShape vertexCircle;
	vertexCircle.setTexture(&m_vertexTexture);
	vertexCircle.setRadius(m_VERTEX_RADIUS);
	vertexCircle.setOrigin(sf::Vector2f(vertexCircle.getRadius(), vertexCircle.getRadius()));
	*/
	for (unsigned int v = 1; v < m_vertices.size(); v++)
	{
		pathRectangle.setTextureRect(sf::IntRect(0, 0, (int)(sqrtf((m_vertices.at(v).x - m_vertices.at(v - 1).x) * (m_vertices.at(v).x - m_vertices.at(v - 1).x)
			+ (m_vertices.at(v).y - m_vertices.at(v - 1).y) * (m_vertices.at(v).y - m_vertices.at(v - 1).y)) + m_PATH_WIDTH), (int)(m_PATH_WIDTH)));

		pathRectangle.setPosition(m_vertices.at(v - 1).x, m_vertices.at(v - 1).y);

		pathRectangle.setRotation(toDegrees(atan2f(m_vertices.at(v).y - m_vertices.at(v - 1).y, m_vertices.at(v).x - m_vertices.at(v - 1).x)));

		m_pathRectangles.push_back(pathRectangle);
		

		if (v != m_vertices.size() - 1)
		{
			//vertexCircle.setPosition(m_vertices.at(v - 1));
			//m_vertexCircles.push_back(vertexCircle);

			vertexSquare.setPosition(m_vertices.at(v - 1));
			vertexDiamond.setPosition(m_vertices.at(v - 1));
			m_vertexStars.push_back(vertexSquare);
			m_vertexStars.push_back(vertexDiamond);
		}
		else
		{
			//vertexCircle.setPosition(m_vertices.at(v - 1));
			//m_vertexCircles.push_back(vertexCircle);

			//vertexCircle.setPosition(m_vertices.at(v));
			//m_vertexCircles.push_back(vertexCircle);

			vertexSquare.setPosition(m_vertices.at(v - 1));
			vertexDiamond.setPosition(m_vertices.at(v - 1));
			m_vertexStars.push_back(vertexSquare);
			m_vertexStars.push_back(vertexDiamond);

			vertexSquare.setPosition(m_vertices.at(v));
			vertexDiamond.setPosition(m_vertices.at(v));
			m_vertexStars.push_back(vertexSquare);
			m_vertexStars.push_back(vertexDiamond);
		}
		
	}
}

void Path::update()
{

}

void Path::render(sf::RenderTarget& renderer)
{
	for (auto& rect : m_pathRectangles) { renderer.draw(rect); }

	//for (auto& circ : m_vertexCircles) { renderer.draw(circ); }

	for (auto& diam : m_vertexStars) { renderer.draw(diam); }
}

void Path::clear()
{
	m_vertices.clear();
	m_pathRectangles.clear();
	//m_vertexCircles.clear();
	m_vertexStars.clear();
}

float Path::getLength()
{
	m_pathLength = 0;

	for (unsigned int i = 1; i < m_vertices.size(); i++)
	{
		m_pathLength = m_pathLength
			+ sqrt((m_vertices.at(i).x - m_vertices.at(i - 1).x) * (m_vertices.at(i).x - m_vertices.at(i - 1).x)
				+ (m_vertices.at(i).y - m_vertices.at(i - 1).y) * (m_vertices.at(i).y - m_vertices.at(i - 1).y));
	}

	//std::cout << "PATH LENGTH IS: " << std::to_string(m_pathLength) << std::endl;
	return m_pathLength;
}

std::vector<sf::Vector2f>& Path::getVertices() { return m_vertices; }

void Path::setWidth(float width) { m_PATH_WIDTH = width; }

float Path::getWidth() const { return m_PATH_WIDTH; }

float Path::getVertexWidth() const { return m_STAR_WIDTH; }
