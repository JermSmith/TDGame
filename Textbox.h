#pragma once

#include <functional>
#include "Widget.h"

namespace gui
{
	class TextBox : public gui::Widget
	{
	public:
		TextBox(std::string& modString);

		void setLabel(const std::string& str);
		//void setTexture(const sf::Texture& tex);

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override;
		void render(sf::RenderTarget& renderer) override;
		void setPosition(const sf::Vector2f& pos) override;
		sf::Vector2f getSize() const override;
		int getMaxNumInRow() const override;
		int getPositionInRow() const override;
		void setPositionInRow(const int) override;
		int getPositionInMenu() const override;
		void setPositionInMenu(const int) override;

		bool isRolledOn(const sf::RenderWindow& window) const override;

	private:
		void handleClick(sf::Event e, const sf::RenderWindow& window);
		void handleTextInput(sf::Event e);

		bool isValidCharacter(unsigned char keyCode);
		bool isBackspace(unsigned char keyCode);

		sf::Vector2f m_position;

		//Rectangle m_rect;
		sf::RectangleShape m_rect;
		//Text m_text;
		Text m_label;
		std::string* m_pModString; // pointer

		bool m_isActive = false;
	};

	inline std::unique_ptr<TextBox> makeTextBox(std::string& modStr) { return std::make_unique<TextBox>(modStr); }
}

