#pragma once

#include "Widget.h"
//#include "InteractableShape.h"

namespace gui
{
	//class Banner : public InteractableShape, public gui::Widget
	class Banner : public gui::Widget
	{
	public:
		Banner(float width, float height);

		void setText(const std::string& str);

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
		void render(sf::RenderTarget& renderer) override;
		void update(const sf::RenderWindow& window) override;
		//void setPosition(const sf::Vector2f& pos) override;
		sf::Vector2f getSize() const override;
		int getMaxNumInRow() const override;
		int getPositionInRow() const override; 
		void setPositionInRow(const int) override;

	private:
		//sf::Vector2f m_position;
		//Text m_text;
	};

	inline Banner makeBanner(float width, float height) { return Banner(width, height); }
	inline Banner makeBanner(sf::Vector2f rectangleDim) { return Banner(rectangleDim.x, rectangleDim.y); }
}


