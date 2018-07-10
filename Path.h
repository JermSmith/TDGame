#pragma once

#include "ResourceManager\ResourceHolder.h"
//#include "Vertex.h"
#include <vector>


class Path// : public GameObject
{
public:

	Path();

	void createRandomPath(int numInternalVertices = 5);
	void createCustomPath(std::vector<sf::Vector2f>& vertices);

	std::vector<sf::Vector2f>& getVertices();
	float getLength();

	void setWidth(float width);
	float getWidth() const;

	void update();
	void render(sf::RenderTarget& target);

private:
	float m_pathLength;
	float m_width;

	std::vector<sf::Vector2f> m_vertices;
	
	// number of vertices in path, not including start and end point
	int m_numVertices;

	sf::Vector2f m_firstVertex = { 480, 0 };
	sf::Vector2f m_lastVertex = { 0, 480 };

	bool isVertexOnPath(sf::Vector2f& vertex);

	sf::Sprite m_sprite;

	//testing
	std::vector<sf::RectangleShape> m_rectPath;

	std::vector<sf::Sprite> m_spritePath;
	void generateSpritePath();

};