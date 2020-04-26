#pragma once

#include "Widget.h"

namespace gui
{
	class Banner : public gui::Widget
	{
	public:
		Banner();

		void setText(const std::string& str);

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
		void render(sf::RenderTarget& renderer) override;
		void update(const sf::RenderWindow& window) override;
		void setPosition(const sf::Vector2f& pos) override;
		sf::Vector2f getSize() const override;
		int getMaxNumInRow() const override;
		int getPositionInRow() const override; 
		void setPositionInRow(const int) override;

	private:
		sf::Vector2f m_position;
		sf::RectangleShape m_rect;
		Text m_text;
	};

	inline Banner makeBanner() { return Banner(); }
}

