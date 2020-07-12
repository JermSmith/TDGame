#pragma once
#include <SFML\Graphics.hpp>

class InteractableShape
{
public:
	InteractableShape(float radius, int pointCount);
	InteractableShape(float width, float height);
	void defineShape(float radius, int pointCount);
	void defineShape(float width, float height);
	int getPointCount() const;
	bool isRolledOn(const sf::RenderWindow& window) const;
	void render(sf::RenderTarget& renderer);
	// returns 1/2width for rectangles, returns radius for greater-than-5-gons
	float getPrimaryDim() const;
	sf::FloatRect getGlobalBounds() const;
	void setOrigin(const sf::Vector2f& origin);
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);
	sf::Color getFillColour() const;
	void setFillColour(const sf::Color& colour);
	void setRolledAppearance();
	void removeRolledAppearance();
	void setClickedAppearance();
	void removeClickedAppearance();
	void setOutlineThickness(const float& thickness);
	void setOutlineColour(const sf::Color& colour);
	void setTexture(const sf::Texture& tex);
	bool bIsRegularPolygon() const;

private:

	sf::ConvexShape m_shape;
	sf::Color m_originalFillColour = sf::Color(-1, -1, -1);

};

