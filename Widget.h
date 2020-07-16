#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include "ResourceManager\ResourceHolder.h"
#include "InteractableShape.h"
#include "Util\Math.h"

namespace gui
{
	class Widget : virtual public InteractableShape
	{
	public:
		void setText(const std::string& str);

		virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;

		virtual void render(sf::RenderTarget& renderer) = 0;
		
		virtual void update(const sf::RenderWindow& window) = 0;

		sf::Vector2f getPosition() const;
		
		void setPosition(const sf::Vector2f& pos);

		virtual sf::Vector2f getSize() const = 0;

		virtual int getMaxNumInRow() const = 0;

		// first column is index 0
		virtual int getPositionInRow() const = 0;
		// first column is index 0
		virtual void setPositionInRow(const int) = 0;

		class Text : public sf::Text
		{
		public:
			Text();
		};

	protected:
		Text m_text;
		sf::Vector2f m_position; // centre of shape for both rectangles and circles

		int m_positionInRow = 0;
		int m_positionInMenu = 0;
	};

	namespace ButtonSizes
	{
		constexpr float HOVER_W = (float)sizes::HOVERMENU_X - 12.f;
		constexpr float HOVER_H = 24.f;
		const sf::Vector2f HOVER = sf::Vector2f(sizes::HOVERMENU_X - 12, 24);

		constexpr float RECT_LG_W = 256.f;
		constexpr float RECT_LG_H = 36.f;
		const sf::Vector2f RECT_LG = sf::Vector2f(256, 36);

		constexpr float RECT_THIN_W = 256.f;
		constexpr float RECT_THIN_H = 18.f;
		const sf::Vector2f RECT_THIN = sf::Vector2f(256, 18);

		constexpr float RECT_SM_W = 150.f;
		constexpr float RECT_SM_H = 36.f;
		const sf::Vector2f RECT_SM = sf::Vector2f(150, 36);

		constexpr float CIRC_LG_R = 40.f;
		constexpr float CIRC_SM_R = 32.f;
		constexpr int CIRC_NUMPTS = 25;

		constexpr float RECT_BANNER_H = 30.f;
	}
}


