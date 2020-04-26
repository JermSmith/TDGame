#pragma once

#include <functional>
#include "Widget.h"
//#include "InteractableCircle.h"
//#include "InteractableRectangle.h"
#include "InteractableShape.h"

namespace gui
{
	namespace ButtonSizes
	{
		constexpr float RECT_LG_W = 256.f;
		constexpr float RECT_LG_H = 48.f;
		constexpr float RECT_SM_W = 150.f;
		constexpr float RECT_SM_H = 48.f;

		constexpr float CIRC_LG_R = 40.f;
		constexpr float CIRC_SM_R = 32.f;
		constexpr int CIRC_NUMPTS = 50;
	}

	class Button : public InteractableShape, public gui::Widget
	{
	public:
		Button(const float& radius, const int& numPts);
		Button(const float& width, const float& height);

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

	inline Button makeButton(const float& radius, const int& numPts) { return Button(radius, numPts); }
	inline Button makeButton(const float& width, const float& height) { return Button(width, height); }
};

	
