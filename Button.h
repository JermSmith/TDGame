#pragma once

#include <functional>
#include "Widget.h"

namespace gui
{
	enum class ButtonSize
	{
		Small, // placed in 1 column
		Wide, // placed in 2 columns
		Circle2, // placed in 2 columns
		Circle3, // placed in 3 columns
	};

	class Button : public gui::Widget
	{
	public:
		Button(ButtonSize s);

		void setFunction(std::function<void(void)> func);
		void setText(const std::string& str);
		void setTexture(const sf::Texture& tex);

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
		void render(sf::RenderTarget& renderer) override;
		void setPosition(const sf::Vector2f& pos) override;
		sf::Vector2f getSize() const override;
		int getNumColumns() const override;

	private:
		void updateText();

		sf::Vector2f m_position; // centre of shape for both rectangles and circles

		sf::ConvexShape m_button;
		ButtonSize m_buttonSize;

		Text m_text;
		std::function<void(void)> m_function = [](){};
	};

	inline std::unique_ptr<Button> makeButton(ButtonSize s) { return std::make_unique<Button>(s); }
}