#pragma once

#include <functional>
#include "Widget.h"
#include "InteractableShape.h"

namespace gui
{
	class Button : public InteractableShape, public gui::Widget
	{
	public:
		Button(float radius, int numPts);
		Button(float width, float height);

		void setFunction(std::function<void(void)> func);
		void setText(const std::string& str);
		void setTexture(const sf::Texture& tex);

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
		void render(sf::RenderTarget& renderer) override;
		void update(const sf::RenderWindow& window) override;
		void setPosition(const sf::Vector2f& pos) override;
		sf::Vector2f getSize() const override;
		int getMaxNumInRow() const override;
		int getPositionInRow() const override;
		void setPositionInRow(const int) override;

	private:
		std::function<void(void)> m_function = []() {};
		sf::Vector2f m_position; // centre of shape for both rectangles and circles
		Text m_text;
	};

	inline Button makeButton(float radius, int numPts) { return Button(radius, numPts); }
	inline Button makeButton(float width, float height) { return Button(width, height); }
};

	
