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
		StackMenu(const sf::RenderWindow& window, float basePositionY);
		StackMenu(float basePositionY);// const sf::Vector2f& basePosition, const sf::Vector2f& baseSize);

		//StackMenu(StackMenu&& other);
		//StackMenu& operator =(StackMenu&& other);

		~StackMenu() = default;

		void clearWidgets();
		bool bContainsWidgets();
		//first pos is 0
		void updateWidgetText(int widgetPosInMenu, std::string newText);
		//void addWidget(std::unique_ptr<Widget> w);
		void addWidget(Widget &w);
		
		/*template<typename T, typename... Args> void addWidget(Args&&... args)
		{
			auto w = std::make_unique<T>(std::forward<Args>(args)...);
			initWidget(*w);
			m_widgets.push_back(std::move(w));
		}*/
		
		//void setTitle(const std::string& title);

		void handleEvent(sf::Event e, const sf::RenderWindow& window);
		void render(sf::RenderTarget& renderer);

		static const int WIDGET_SPACER = 15;

	private:
		//const sf::RenderWindow& getWindow() const;
		float m_origBasePositionY = 0;
		//float m_origBaseSizeY;

		void initWidget(Widget &w);
		bool m_bIsFirstWidgetInMenu = true;

		//const sf::RenderWindow* m_pWindow;

		//std::vector<std::unique_ptr<Widget>> m_widgets;
		std::vector<Widget*> m_widgets;
		sf::RectangleShape m_background;

		sf::Vector2f m_basePosition; //top centre point of menu
		sf::Vector2f m_baseSize; //(width, height) of menu

		//Widget::Text m_titleText;
	};
}

