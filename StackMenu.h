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
		StackMenu(const sf::Vector2f& topCentrePoint, float menuWidth, float outlineThickness, sf::Uint8 backgroundTransparency);

		//StackMenu(StackMenu&& other);
		//StackMenu& operator =(StackMenu&& other);

		/*template<typename T, typename... Args> void addWidget(Args&&... args)
		{
			auto w = std::make_unique<T>(std::forward<Args>(args)...);
			initWidget(*w);
			m_widgets.push_back(std::move(w));
		}*/

		~StackMenu() = default;

		void clearWidgets();
		bool bContainsWidgets();
		void addWidget(Widget &w);

		std::vector<Widget*> getWidgets() const;

		void handleEvent(sf::Event e, const sf::RenderWindow& window);
		void render(sf::RenderTarget& renderer);

		void hideOutline();
		void showOutline();


	protected:
		int m_widgetSpacer = 15;

		sf::Vector2f m_topCentrePoint;

		sf::RectangleShape m_background;
		sf::Vector2f m_outerDim;

		sf::Color m_origOutlineColour = sf::Color::Green;

	private:
		float m_drawingPos_y;

		void initWidget(Widget &w);
		bool m_bIsFirstWidgetInMenu = true;

		std::vector<Widget*> m_widgets;
	};
}



