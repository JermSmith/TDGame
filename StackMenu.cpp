#include "StackMenu.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

namespace gui
{
	// TODO: consolidate these two constructors into one constructor for both main menu and other menus

	//this constructor is called each time the main menu is made
	StackMenu::StackMenu(const sf::RenderWindow& window, float basePositionY)
		: m_basePosition(((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X) / 2.0f, basePositionY)
		, m_baseSize((float)sizes::MAINMENU_BASESIZE_X, 0)
	{
		m_background.setOutlineThickness(2);
		m_background.setOutlineColor(sf::Color::Green);
		m_background.setFillColor({ 100, 100, 100, 230 });
		m_background.setSize(m_baseSize);
		m_background.setPosition(m_basePosition.x - m_baseSize.x / 2, m_basePosition.y);

		//m_titleText.setPosition(((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X) / 2.0f, m_basePosition.y - 35);
		//m_titleText.setOutlineColor(sf::Color::Black);
		//m_titleText.setOutlineThickness(1);
		//m_titleText.setCharacterSize(30);
		//m_titleText.setString("The Title Of The Game");
	}

	//this constructor is called each time the playing menu or options menu is made
	StackMenu::StackMenu(float basePositionY)//const sf::Vector2f& basePosition, const sf::Vector2f& baseSize)
		: m_basePosition(sf::Vector2f(((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2), basePositionY))
		, m_baseSize(sf::Vector2f((float)sizes::PLAYINGMENU_X, 0))//baseSize)
		, m_origBasePositionY(basePositionY)
	{
		//m_origBasePositionY = basePosition.y;
		//m_origBaseSizeY = baseSize.y;

		m_background.setFillColor({ 100, 100, 100, 128 });
		m_background.setSize(m_baseSize);
		m_background.setPosition(m_basePosition.x - m_baseSize.x / 2, m_basePosition.y);
		// background position is based on its top left corner
	}

	/*StackMenu::StackMenu(StackMenu&& other)
		: m_widgets(std::move(other.m_widgets))
		, m_background(std::move(other.m_background))
		, m_basePosition(other.m_basePosition)
		, m_baseSize(other.m_baseSize)
	{
	}

	StackMenu& StackMenu::operator=(StackMenu&& other)
	{
		m_widgets = std::move(other.m_widgets);
		m_background = std::move(other.m_background);
		m_basePosition = other.m_basePosition;
		m_baseSize = other.m_baseSize;

		return *this;
	}*/

	void StackMenu::clearWidgets()
	{
		m_widgets.clear();
		m_basePosition.y = m_origBasePositionY;
		m_baseSize.y = 0;
		m_background.setSize(m_baseSize);
		m_bIsFirstWidgetInMenu = true;
	}

	bool StackMenu::bContainsWidgets()
	{
		bool bContains;
		if (m_widgets.size() == 0) { bContains = false; }
		else { bContains = true; }
		return bContains;
	}

	void StackMenu::addWidget(Widget& w)
	{
		initWidget(w);
		m_widgets.push_back(&w);
	}

	std::vector<Widget*> StackMenu::getWidgets() const
	{
		return m_widgets;
	}

	// TODO: update to adjust to the fact that the base size doesn't really need to adjust for the playing menu and options menu, only for
	// the main menu, since the playing menu base size is always the same height, but the main menu base size grows as buttons are added.
	void StackMenu::initWidget(Widget &widget)
	{
		// widgets must be added consecutively in the order they are to appear on-screen, reading left to right in rows from top to bottom of menu
		
		// xPos : is the x-coordinate of the top-centre point of a widget
		// n_ : factor to scale the horiz. distance between shapes (relative to the distance from outside border to shape)
		// a_ : uniform horizontal separation between shapes in columnStyle # of columns

		// for 2 circles/row: [whole row width = a + 2*rad + a*n + 2*rad + a]
		// for 3 circles/row: [whole row width = a + 2*rad + a*n + 2*rad + a*n + 2*rad + a]

		float xPos = 0; //this initialization value is meaningless
		float n_ = 0.8f;
		float a_ = (m_baseSize.x - widget.getMaxNumInRow() * widget.getSize().x) / (2.f + (float)(widget.getMaxNumInRow() - 1) * n_);

		if (m_bIsFirstWidgetInMenu)
		{
			m_bIsFirstWidgetInMenu = false;

			m_basePosition.y += WIDGET_SPACER; // first widget will appear at a small gap under the top border
			m_baseSize.y += widget.getSize().y + WIDGET_SPACER * 2; // expand the base from 0 to widgetSize + 2*space
			m_background.setSize(m_baseSize);

			switch (widget.getMaxNumInRow())
			{
			case 1:
				xPos = m_basePosition.x; // centre of row
				break;
			case 2:
				xPos = m_basePosition.x - n_ * a_ / 2.f - widget.getSize().x / 2.f; // x-coord of centre of left-most drawing position
				break;
			case 3:
				xPos = m_basePosition.x - widget.getSize().x - a_ * n_; // x-coord of centre of left-most drawing position
				break;
			}
			// widgets have their origin at their centre
			widget.setPosition({ xPos, m_basePosition.y + widget.getSize().y / 2 });
			widget.setPositionInRow(0);
		}
		else
		{
			if ((widget.getMaxNumInRow() != m_widgets.back()->getMaxNumInRow()) || // new widget has different row layout than last widget
				(m_widgets.back()->getMaxNumInRow() == m_widgets.back()->getPositionInRow() + 1)) // last widget completed a row
			{
				m_basePosition.y += m_widgets.back()->getSize().y + WIDGET_SPACER;
				m_baseSize.y += widget.getSize().y + WIDGET_SPACER;
				m_background.setSize(m_baseSize);
			}
			switch (widget.getMaxNumInRow())
			{
			case 1:
				xPos = m_basePosition.x; // centre of row
				widget.setPositionInRow(0);
				break;

			case 2:
				//specific form for a_ = 2 : a_ = (m_baseSize.x - 2.f * widget.getSize().x) / (2.f + n_);

				if (m_widgets.back()->getMaxNumInRow() == 2 && m_widgets.back()->getPositionInRow() == 0)
				{
					xPos = m_basePosition.x + n_ * a_ / 2.f + widget.getSize().x / 2.f; // (top-centre of) right circle
					widget.setPositionInRow(1);
				}
				else // this will be the first (left-most) object in the a new row
				{
					xPos = m_basePosition.x - n_ * a_ / 2.f - widget.getSize().x / 2.f; // (top-centre of) left circle
					widget.setPositionInRow(0);
				}

				break;

			case 3:
				//specific form for a_ = 3 : a_ = (m_baseSize.x - 3.f * widget.getSize().x) / (2.f + 2.f * n_);

				if (m_widgets.back()->getMaxNumInRow() == 3 && m_widgets.back()->getPositionInRow() == 1)
				{// prev widget was placed in middle spot
					xPos = m_basePosition.x + widget.getSize().x + a_ * n_; // (top-centre of) right-most spot
					widget.setPositionInRow(2);
				}
				else if (m_widgets.back()->getMaxNumInRow() == 3 && m_widgets.back()->getPositionInRow() == 0)
				{// prev widget was placed in left-most spot
					xPos = m_basePosition.x; // (top-centre of) middle circle
					widget.setPositionInRow(1);
				}
				else
				{// last widget either had a different "max num in row" scheme, or was placed in the right-most spot (finishing the row)
					xPos = m_basePosition.x - widget.getSize().x - a_ * n_; // (top-centre of) left-most spot
					widget.setPositionInRow(0);
				}
				break;
			}
			widget.setPosition({ xPos, m_basePosition.y + widget.getSize().y / 2 });
		}
	}

	//void StackMenu::setTitle(const std::string& title)
	//{
	//	m_titleText.setString(title);
	//	m_titleText.setPosition(getWindow().getSize().x - m_titleText.getGlobalBounds().width / 2, m_titleText.getPosition().y);
	//}

	void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		for (unsigned int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->handleEvent(e, window);
		}
	}

	void StackMenu::render(sf::RenderTarget& renderer)
	{
		renderer.draw(m_background);
		//renderer.draw(m_titleText);
		for (unsigned int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->render(renderer);
		}
		/*for (gui::Widget* widget : m_widgets)
		{
			widget->render(renderer);
		}*/
	}

	//const sf::RenderWindow& StackMenu::getWindow() const
	//{
	//	return *m_pWindow;
	//}

}


