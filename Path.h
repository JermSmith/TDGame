#pragma once

#include "ResourceManager\ResourceHolder.h" // load textures for path and vertices
#include "Util\Math.h" // game dimension constants
#include <vector>

class Path
{
public:

	Path();

	void createRandomPath(int numInternalVertices);
	void createOrthoPath(int numInternalVertices);
	void createCustomPath(std::vector<sf::Vector2f>& vertices);

	const std::vector<sf::Vector2f>& getVertices() const;
	const float getLength(); // calculates length before it returns it, so function is not const

	const float getWidth() const;
	const float getVertexWidth() const;

	void setWidth(float width);

	void clear();

	void update();
	void render(sf::RenderTarget& target);

private:

	bool vertexInterferesWithPath(sf::Vector2f& vertex);
	void generateSprites();

	sf::Vector2f m_firstVertex;
	sf::Vector2f m_lastVertex;

	float m_pathLength = 0;

	float m_PATH_WIDTH = 40;
	//m_VERTEX_RADIUS = m_PATH_WIDTH * (float)1.25;
	float m_STAR_WIDTH = m_PATH_WIDTH * (float)1.25; // side length of square or diamond in the star

	float m_VRTX_EDGE_CLRNCE = m_STAR_WIDTH * 2;

	float m_TOLERANCE = m_STAR_WIDTH + m_PATH_WIDTH;
	int m_MAX_NUM_LOOPS = 20;

	float m_LEFT_BORDER = m_PATH_WIDTH;
	float m_TOP_BORDER = m_PATH_WIDTH;

	float m_RIGHT_BORDER = (float)(sizes::WORLD_SIZE_X - sizes::PLAYINGMENU_X) - m_PATH_WIDTH; // largest x-val for vertex position
	float m_BOTTOM_BORDER = (float)sizes::WORLD_SIZE_Y - m_PATH_WIDTH; //largest y-val for vertex position

	std::vector<sf::Vector2f> m_vertices;
	
	int m_numVertices; // number of vertices in path, not including start and end point

	sf::Texture m_pathTexture;
	sf::Texture m_vertexTexture;

	std::vector<sf::Sprite> m_pathRectangles;
	//std::vector<sf::CircleShape> m_vertexCircles;
	std::vector<sf::Sprite> m_vertexStars;
	sf::Sprite m_startArrowRect;
	sf::ConvexShape m_startArrowTriangle;

};

