#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include "ResourceManager\ResourceHolder.h"

namespace gui
{
	class Widget
	{
	public:
		void setText(const std::string& str);

		virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;

		virtual void render(sf::RenderTarget& renderer) = 0;

		virtual void setPosition(const sf::Vector2f& pos) = 0;

		virtual sf::Vector2f getSize() const = 0;

		virtual int getMaxNumInRow() const = 0;

		// first column is index 0
		virtual int getPositionInRow() const = 0;
		// first column is index 0
		virtual void setPositionInRow(const int) = 0;

		//virtual int getPositionInMenu() const = 0;
		//virtual void setPositionInMenu(const int) = 0;

		virtual bool isRolledOn(const sf::RenderWindow& window) const = 0;

		class Text : public sf::Text
		{
		public:
			Text();
		};

		//class Rectangle : public sf::RectangleShape
		//{
		//public:
		//virtual bool isRolledOn(const sf::RenderWindow& window) const = 0;
			//bool isClicked(sf::Event, const sf::RenderWindow& window);
		//};

		// class Circle... public convex shape?

	protected:
		Text m_text;
		
		int m_positionInRow = 0;
		int m_positionInMenu = 0;
	};
}

