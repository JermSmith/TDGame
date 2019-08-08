#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>

#include "Widget.h"
#include "Util\NonCopyable.h"

namespace gui
{
	class StackMenu : public NonCopyable
	{
	public:
		StackMenu(const sf::RenderWindow& window, float baseY);
		StackMenu(const sf::Vector2f& basePosition, const sf::Vector2f& baseSize);

		StackMenu(StackMenu&& other);
		StackMenu& operator =(StackMenu&& other);

		~StackMenu() = default;

		void addWidget(std::unique_ptr<Widget> w);
		/*
		template<typename T, typename... Args> void addWidget(Args&&... args)
		{
			auto w = std::make_unique<T>(std::forward<Args>(args)...);
			initWidget(*w);
			m_widgets.push_back(std::move(w));
		}*/
		
		void setTitle(const std::string& title);

		void handleEvent(sf::Event e, const sf::RenderWindow& window);
		void render(sf::RenderTarget& renderer);

		static const int WIDGET_SPACER = 25;

	private:
		const sf::RenderWindow& getWindow() const;

		void initWidget(Widget& w);
		int m_prevNumColumns = 1; // default is to place widgets in a single column
		int m_consecutiveColumnStyleCount = 0; // no widgets have been placed at initialization

		const sf::RenderWindow* m_pWindow;

		std::vector<std::unique_ptr<Widget>> m_widgets;
		sf::RectangleShape m_background;

		sf::Vector2f m_basePosition; //top centre point of menu
		sf::Vector2f m_baseSize; //(width, height) of menu

		Widget::Text m_titleText;
	};
}