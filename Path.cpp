#include "Path.h"

#include "Util\Random.h" // random number generator
#include <iostream> // getLength function
#include <string> // getLength function

Path::Path()
{
	m_pathTexture = ResourceHolder::get().textures.get("grass");
	m_pathTexture.setRepeated(true);

	m_vertexTexture = ResourceHolder::get().textures.get("wood");
	m_vertexTexture.setRepeated(true);
}

void Path::createRandomPath(int numInternalVertices)
{
	bool bfailed;
	do
	{
		bfailed = false;

		m_numVertices = numInternalVertices;
		static Random<> rand;
		clear();
		int rand50_firstVertex_1 = rand.getIntInRange(0, 1);
		int rand50_firstVertex_2 = rand.getIntInRange(0, 1);
		int rand50_lastVertex_1 = rand.getIntInRange(0, 1);
		int rand50_lastVertex_2 = rand.getIntInRange(0, 1);
		float randX;
		float randY;

		if (m_numVertices == 0) { m_numVertices = rand.getIntInRange(1, 6); }

		// generate first vertex
		switch (rand50_firstVertex_1)
		{
		case 0:
			randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
			// hold first vertex at least vrtx_edge_clrnce units from corner
			switch (rand50_firstVertex_2)
			{
			case 0:
				m_firstVertex = sf::Vector2f(randX, m_TOP_BORDER);
				break;
			case 1:
				m_firstVertex = sf::Vector2f(randX, m_BOTTOM_BORDER);
				break;
			}

			break;

		case 1:
			randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
			// hold first vertex at least vrtx_edge_clrnce units from corner
			switch (rand50_firstVertex_2)
			{
			case 0:
				m_firstVertex = sf::Vector2f(m_LEFT_BORDER, randY);
				break;
			case 1:
				m_firstVertex = sf::Vector2f(m_RIGHT_BORDER, randY);
				break;
			}

			break;
		}
		m_vertices.push_back(m_firstVertex); // first vertex added

		if (m_numVertices == 1)
		{
			randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
			randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
			// hold vertices at least vrtx_edge_clrnce units away from the edge
			m_vertices.push_back(sf::Vector2f(randX, randY)); // add the only internal vertex

			int tries = 0;
			do
			{
				switch (rand50_lastVertex_1)
				{
				case 0:
					randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
					switch (rand50_lastVertex_2)
					{
					case 0:
						m_lastVertex = sf::Vector2f(randX, m_TOP_BORDER);
						break;
					case 1:
						m_lastVertex = sf::Vector2f(randX, m_BOTTOM_BORDER);
						break;
					}

					break;

				case 1:
					randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
					switch (rand50_lastVertex_2)
					{
					case 0:
						m_lastVertex = sf::Vector2f(m_LEFT_BORDER, randY);
						break;
					case 1:
						m_lastVertex = sf::Vector2f(m_RIGHT_BORDER, randY);
						break;
					}

					break;
				}

				tries++;
				if (tries == m_MAX_NUM_LOOPS) { bfailed = true; }
				// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation
			} while (vertexInterferesWithPath(m_lastVertex) && tries < m_MAX_NUM_LOOPS);

			m_vertices.push_back(m_lastVertex);

			generateSprites();
			return; // leave the function early
		}

		for (int v = 1; v <= m_numVertices + 1; v++) // +1 to numVertices to account for last vertex
		{
			if (v != m_numVertices + 1) // deal with all vertices except the last vertex
			{
				int tries = 0;
				do
				{
					randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
					randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
					// hold vertices at least vrtx_edge_clrnce units away from the edge
					tries++;
					if (tries == m_MAX_NUM_LOOPS) { bfailed = true; }
					// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation
				} while (vertexInterferesWithPath(sf::Vector2f(randX, randY)) && tries < m_MAX_NUM_LOOPS);

				m_vertices.push_back(sf::Vector2f(randX, randY));
			}


			else if (v == m_numVertices + 1) // add the last vertex
			{
				int tries = 0;
				do
				{
					switch (rand50_lastVertex_1)
					{
					case 0:
						randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
						switch (rand50_lastVertex_2)
						{
						case 0:
							m_lastVertex = sf::Vector2f(randX, m_TOP_BORDER);
							break;
						case 1:
							m_lastVertex = sf::Vector2f(randX, m_BOTTOM_BORDER);
							break;
						}

						break;

					case 1:
						randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
						switch (rand50_lastVertex_2)
						{
						case 0:
							m_lastVertex = sf::Vector2f(m_LEFT_BORDER, randY);
							break;
						case 1:
							m_lastVertex = sf::Vector2f(m_RIGHT_BORDER, randY);
							break;
						}

						break;
					}

					tries++;
					if (tries == m_MAX_NUM_LOOPS) { bfailed = true; }
					// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation
				} while (vertexInterferesWithPath(m_lastVertex) && tries < m_MAX_NUM_LOOPS);

				m_vertices.push_back(m_lastVertex);
			}
		}

		generateSprites();

	}
	while (bfailed);

}

void Path::createOrthoPath(int numInternalVertices)
{
	bool bfailed;
	do
	{
		bfailed = false;

		m_numVertices = numInternalVertices;
		static Random<> rand;
		clear();
		int rand50_firstVertex_1 = rand.getIntInRange(0, 1);
		int rand50_firstVertex_2 = rand.getIntInRange(0, 1);
		int rand50_lastVertex = rand.getIntInRange(0, 1);
		float randX;
		float randY;
		sf::Vector2f newVertex;

		if (m_numVertices == 0) { m_numVertices = rand.getIntInRange(1, 6); }

		// generate first vertex
		switch (rand50_firstVertex_1)
		{
		case 0:
			randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE * (float)1.5, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE * (float)1.5);
			// do not let first x-val get too close to the corners
			// for an ortho path, placing a vertex in a corner is more problematic, so we do vrtxedgeclrnce*1.5 (same for case 1 and default)
			switch (rand50_firstVertex_2)
			{
			case 0:
				m_firstVertex = sf::Vector2f(randX, m_TOP_BORDER);
				break;
			case 1:
				m_firstVertex = sf::Vector2f(randX, m_BOTTOM_BORDER);
				break;
			}

			break;

		case 1:
			randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE * (float)1.5, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE * (float)1.5);
			// do not let first y-val get too close to the corners

			switch (rand50_firstVertex_2)
			{
			case 0:
				m_firstVertex = sf::Vector2f(m_LEFT_BORDER, randY);
				break;
			case 1:
				m_firstVertex = sf::Vector2f(m_RIGHT_BORDER, randY);
				break;
			}

			break;
		}
		m_vertices.push_back(m_firstVertex); // first vertex added

		if (m_numVertices == 1)
		{
			if (m_firstVertex.y == m_TOP_BORDER || m_firstVertex.y == m_BOTTOM_BORDER)
			{
				randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
				// hold a vertex at least vrtx_edge_clrnce units away from the edge
				m_vertices.push_back(sf::Vector2f(m_firstVertex.x, randY));
				switch (rand50_lastVertex)
				{
				case 0:
					m_lastVertex = sf::Vector2f(m_LEFT_BORDER, randY);
					m_vertices.push_back(m_lastVertex);
					break;
				case 1:
					m_lastVertex = sf::Vector2f(m_RIGHT_BORDER, randY);
					m_vertices.push_back(m_lastVertex);
					break;
				}

			}
			else if (m_firstVertex.x == m_LEFT_BORDER || m_firstVertex.x == m_RIGHT_BORDER)
			{
				randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
				// hold a vertex at least vrtx_edge_clrnce units away from the edge
				m_vertices.push_back(sf::Vector2f(randX, m_firstVertex.y));
				switch (rand50_lastVertex)
				{
				case 0:
					m_lastVertex = sf::Vector2f(randX, m_TOP_BORDER);
					m_vertices.push_back(m_lastVertex);
					break;
				case 1:
					m_lastVertex = sf::Vector2f(randX, m_BOTTOM_BORDER);
					m_vertices.push_back(m_lastVertex);
					break;
				}
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
					if (m_firstVertex.x == m_LEFT_BORDER || m_firstVertex.x == m_RIGHT_BORDER)
					{
						randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
						// hold a vertex at least vrtx_edge_clrnce units away from the edge

						newVertex = sf::Vector2f(randX, m_firstVertex.y);
						m_vertices.push_back(newVertex);
					}
					else if (m_firstVertex.y == m_TOP_BORDER || m_firstVertex.y == m_BOTTOM_BORDER)
					{
						randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
						// hold a vertex at least vrtx_edge_clrnce units away from the edge

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
							randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
							// hold a vertex at least vrtx_edge_clrnce units away from the edge
							newVertex = sf::Vector2f(randX, m_vertices.at(v).y);
							tries++;
							if (tries == m_MAX_NUM_LOOPS) { bfailed = true; }
							// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation
						} while (vertexInterferesWithPath(newVertex) && tries < m_MAX_NUM_LOOPS);

						m_vertices.push_back(newVertex);
					}
					else if (m_vertices.at(v).y == m_vertices.at(v - 1).y) // last move was horizontal
					{
						int tries = 0;
						do
						{
							randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
							// hold a vertex at least vrtx_edge_clrnce units away from the edge
							newVertex = sf::Vector2f(m_vertices.at(v).x, randY);
							tries++;
							if (tries == m_MAX_NUM_LOOPS) { bfailed = true; }
							// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation
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
							randX = rand.getFloatInRange(m_LEFT_BORDER + m_VRTX_EDGE_CLRNCE, m_RIGHT_BORDER - m_VRTX_EDGE_CLRNCE);
							// hold a vertex at least vrtx_edge_clrnce units away from the edge
							newVertex = sf::Vector2f(randX, m_vertices.at(v).y); // second-last vertex (actually the final internal vertex)
							switch (rand50_lastVertex)
							{
							case 0:
								m_lastVertex = sf::Vector2f(randX, m_TOP_BORDER);
								break;
							case 1:
								m_lastVertex = sf::Vector2f(randX, m_BOTTOM_BORDER);
								break;
							}

							tries1++;

							if (tries1 == m_MAX_NUM_LOOPS) { bfailed = true; }
							// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation

						} while (vertexInterferesWithPath(newVertex) && tries1 < m_MAX_NUM_LOOPS);
						// the above vertex inferference check is not yet for last vertex, only for second-last vertex

						m_vertices.push_back(newVertex);  // second-last vertex (actually the final internal vertex)
						// the interference check for lastVertex only works correctly after newVertex has been added

						tries2++;
						if (tries2 == m_MAX_NUM_LOOPS) { bfailed = true; }

						// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation
					} while (vertexInterferesWithPath(m_lastVertex) && tries2 < m_MAX_NUM_LOOPS);
					// vertex interference check for last vertex

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
							randY = rand.getFloatInRange(m_TOP_BORDER + m_VRTX_EDGE_CLRNCE, m_BOTTOM_BORDER - m_VRTX_EDGE_CLRNCE);
							// hold a vertex at least vrtx_edge_clrnce units away from the edge
							newVertex = sf::Vector2f(m_vertices.at(v).x, randY);  // second-last vertex (actually the final internal vertex)
							switch (rand50_lastVertex)
							{
							case 0:
								m_lastVertex = sf::Vector2f(m_LEFT_BORDER, randY);
								break;
							case 1:
								m_lastVertex = sf::Vector2f(m_RIGHT_BORDER, randY);
								break;
							}

							tries1++;
							if (tries1 == m_MAX_NUM_LOOPS) { bfailed = true; }
							// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation
						} while (vertexInterferesWithPath(newVertex) && tries1 < m_MAX_NUM_LOOPS);

						m_vertices.push_back(newVertex);  // second-last vertex (actually the final internal vertex)
						// the interference check for lastVertex only works correctly after newVertex has been added
						tries2++;
						if (tries2 == m_MAX_NUM_LOOPS) { bfailed = true; }
						// if loops "m_MAX_NUM_LOOPS" times, then let pass with a failed note to restart path calculation
					} while (vertexInterferesWithPath(m_lastVertex) && tries2 < m_MAX_NUM_LOOPS);

					m_vertices.push_back(m_lastVertex);
				}
			}
		}

		generateSprites();
	}
	while (bfailed);
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
	float dr = 4; // resolution to check for interference
	float dx;
	float dy;
	float theta;

	sf::Vector2f p0;
	sf::Vector2f p1;
	
	/* the only differences between the two for-loops below are the assignment of p0 and p1,
		and points/vertices used to check for intersection */

	// check if new path segment is too short
	p0 = m_vertices.back(); // soon-to-be second-last vertex
	p1 = vertex; // vertex to be placed
	if (distanceBetweenPoints(p0.x, p0.y, p1.x, p1.y) <= m_TOLERANCE)
	{
		return true;
	}
		
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
			// cos and sin are here to make the inequalities work - the real check is between p0.x and p1.x and p0.y and p1.y
			// p0.x and p0.y increment while p1.x/y stay constant, so eventually p0.x/y will overtake p1.x/y, then that path segment is done
		{
			// check intersection
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

	float angleInRad = atan2f(m_vertices.at(1).y - m_vertices.at(0).y, m_vertices.at(1).x - m_vertices.at(0).x);
	float offsetFromVertex = m_STAR_WIDTH / (float)1.4;
	float straightLength = 72;
	while (distanceBetweenPoints(m_vertices.at(0).x, m_vertices.at(0).y, m_vertices.at(1).x, m_vertices.at(1).y) < straightLength + offsetFromVertex * 2)
	{
		straightLength = straightLength / 2; // shorten the straight portion of the arrow, since the first two vertices are close together
		offsetFromVertex = offsetFromVertex / 2; // move the arrow closer to the starting vertex
	}

	m_startArrowRect.setTexture(m_vertexTexture);
	m_startArrowRect.setColor(sf::Color::Red);
	m_startArrowRect.setTextureRect(sf::IntRect(0, 0, (int)straightLength, (int)m_PATH_WIDTH / 2));
	m_startArrowRect.setOrigin(0, m_PATH_WIDTH / 4); //flat end of the arrow, at half of its thickness
	m_startArrowRect.setRotation(toDegrees(angleInRad));
	m_startArrowRect.setPosition(m_vertices.at(0).x + offsetFromVertex * cosf(angleInRad)
		, m_vertices.at(0).y + offsetFromVertex * sinf(angleInRad));

	//				|\
	//				|  \
	//    origin -->|	>
	//				|  /
	//				|/
	m_startArrowTri.setTexture(&m_vertexTexture);
	m_startArrowTri.setFillColor(sf::Color::Red);
	m_startArrowTri.setPointCount(3); // then define the 3 points of the triangle below
	m_startArrowTri.setPoint(0, sf::Vector2f(0, 0));
	m_startArrowTri.setPoint(1, sf::Vector2f(0, m_PATH_WIDTH));
	m_startArrowTri.setPoint(2, sf::Vector2f(m_PATH_WIDTH / 2, m_PATH_WIDTH * cosf(MIN_PI / 3)));
	m_startArrowTri.setOrigin(sf::Vector2f(0, m_PATH_WIDTH / 2)); //set origin to be midpoint of base
	m_startArrowTri.setRotation(toDegrees(angleInRad));
	m_startArrowTri.setPosition(m_vertices.at(0).x + (offsetFromVertex + straightLength) * cosf(angleInRad)
		, m_vertices.at(0).y + (offsetFromVertex + straightLength) * sinf(angleInRad));

}

void Path::update()
{

}

void Path::render(sf::RenderTarget& renderer)
{
	for (auto& rect : m_pathRectangles) { renderer.draw(rect); }

	//for (auto& circ : m_vertexCircles) { renderer.draw(circ); }

	for (auto& diam : m_vertexStars) { renderer.draw(diam); }

	renderer.draw(m_startArrowRect);
	renderer.draw(m_startArrowTri);
}

void Path::clear()
{
	m_vertices.clear();
	m_pathRectangles.clear();
	//m_vertexCircles.clear();
	m_vertexStars.clear();
	m_startArrowRect.setColor(sf::Color::Transparent);
	m_startArrowTri.setFillColor(sf::Color::Transparent);
}

const float Path::getLength()
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

const std::vector<sf::Vector2f>& Path::getVertices() const { return m_vertices; }

void Path::setWidth(float width) { m_PATH_WIDTH = width; }

const float Path::getWidth() const { return m_PATH_WIDTH; }

const float Path::getVertexWidth() const { return m_STAR_WIDTH; }
