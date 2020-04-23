#pragma once

#include <functional>
#include "Widget.h"
#include "InteractableShape.h"

namespace gui
{
	enum class ButtonSize
	{
		Wide, // placed in 1 column
		Small, // placed in 2 columns
		Circle2, // placed in 2 columns
		Circle3, // placed in 3 columns
	};

	class CircularButton : public gui::Widget, public InteractableShape
	{
	public:
		void setFunction(std::function<void(void)> func);
		//void setText(const std::string& str);
		void setTexture(const sf::Texture& tex);
		void render(sf::RenderTarget& renderer) override;
		void setPosition(const sf::Vector2f& pos) override;
		sf::Vector2f getSize() const override;
		int getMaxNumInRow() const override;
		int getPositionInRow() const override;
		void setPositionInRow(const int) override;
		//int getPositionInMenu() const override;
		//void setPositionInMenu(const int) override;
		
		CircularButton(ButtonSize s);

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override;

		bool isRolledOn(const sf::RenderWindow& window) const override;
	protected:
		sf::ConvexShape m_button;
		std::function<void(void)> m_function = []() {};
		ButtonSize m_buttonSize;
		sf::Vector2f m_position; // centre of shape for both rectangles and circles
		//Text m_text;
	};



	class RectangularButton : public gui::Widget, public InteractableShape
	{
	public:
		void setFunction(std::function<void(void)> func);
		//void setText(const std::string& str);
		void setTexture(const sf::Texture& tex);
		void render(sf::RenderTarget& renderer) override;
		void setPosition(const sf::Vector2f& pos) override;
		sf::Vector2f getSize() const override;
		int getMaxNumInRow() const override;
		int getPositionInRow() const override;
		void setPositionInRow(const int) override;
		//int getPositionInMenu() const override;
		//void setPositionInMenu(const int) override;

		RectangularButton(ButtonSize s);

		void handleEvent(sf::Event e, const sf::RenderWindow& window) override;

		bool isRolledOn(const sf::RenderWindow& window) const override;
	protected:
		sf::ConvexShape m_button;
		std::function<void(void)> m_function = []() {};
		ButtonSize m_buttonSize;
		sf::Vector2f m_position; // centre of shape for both rectangles and circles
		//Text m_text;
	}; 


	//inline std::unique_ptr<CircularButton> makeCircularButton(ButtonSize s) { return std::make_unique<CircularButton>(s); }
	//inline std::unique_ptr<RectangularButton> makeRectangularButton(ButtonSize s) { return std::make_unique<RectangularButton>(s); }

	inline CircularButton makeCircularButton(ButtonSize s) { return CircularButton(s); }
	inline RectangularButton makeRectangularButton(ButtonSize s) { return RectangularButton(s); }

}




