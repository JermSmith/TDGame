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
		StackMenu(const sf::Vector2f& topCentrePoint, float menuWidth, bool bOutline);

		//StackMenu(StackMenu&& other);
		//StackMenu& operator =(StackMenu&& other);

		~StackMenu() = default;

		void clearWidgets();
		bool bContainsWidgets();
		void addWidget(Widget &w);

		std::vector<Widget*> getWidgets() const;
		
		/*template<typename T, typename... Args> void addWidget(Args&&... args)
		{
			auto w = std::make_unique<T>(std::forward<Args>(args)...);
			initWidget(*w);
			m_widgets.push_back(std::move(w));
		}*/

		void handleEvent(sf::Event e, const sf::RenderWindow& window);
		void render(sf::RenderTarget& renderer);

		static const int WIDGET_SPACER = 15;

	private:
		float m_origBasePositionY;

		void initWidget(Widget &w);
		bool m_bIsFirstWidgetInMenu = true;

		std::vector<Widget*> m_widgets;
		sf::RectangleShape m_background;

		sf::Vector2f m_topCentrePoint;
		sf::Vector2f m_outerDim;
	};
}


