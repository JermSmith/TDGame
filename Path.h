#pragma once

#include "ResourceManager\ResourceHolder.h"
#include <vector>

class Path
{
public:

	Path();

	void createRandomPath(int numInternalVertices);
	void createOrthoPath(int numInternalVertices);
	void createCustomPath(std::vector<sf::Vector2f>& vertices);

	std::vector<sf::Vector2f>& getVertices();
	float getLength();

	void setWidth(float width);
	float getWidth() const;
	float getVertexWidth() const;

	void clear();

	void update();
	void render(sf::RenderTarget& target);

private:

	bool vertexInterferesWithPath(sf::Vector2f& vertex);
	void generateSprites();
	//float Path::getDistanceBetweenPoints(sf::Vector2f& v0, sf::Vector2f& v1);

	sf::Vector2f m_firstVertex;
	sf::Vector2f m_lastVertex;

	float m_pathLength;

	float m_PATH_WIDTH;
	//float m_VERTEX_RADIUS;
	float m_STAR_WIDTH; // side length of square or diamond in the star

	float m_TOLERANCE;
	int m_MAX_NUM_LOOPS;

	float m_TOP_BORDER;
	float m_LEFT_BORDER;

	std::vector<sf::Vector2f> m_vertices;
	
	int m_numVertices; // number of vertices in path, not including start and end point

	sf::Texture m_pathTexture;
	sf::Texture m_vertexTexture;

	std::vector<sf::Sprite> m_pathRectangles;
	//std::vector<sf::CircleShape> m_vertexCircles;
	std::vector<sf::Sprite> m_vertexStars;
};