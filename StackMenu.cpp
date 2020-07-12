#include "StackMenu.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

namespace gui
{
	// 1) sf::Vector2f topCentrePoint, 2) float menuWidth, 3) bool bOutline
	StackMenu::StackMenu(const sf::Vector2f& topCentrePoint, float menuWidth, float outlineThickness, sf::Uint8 backgroundTransparency)
		: m_topCentrePoint(topCentrePoint)
		, m_outerDim(menuWidth, 0)
		, m_drawingPos_y(topCentrePoint.y)
	{
			m_background.setOutlineColor(m_origOutlineColour);
			m_background.setOutlineThickness(outlineThickness);
			m_background.setFillColor({ 100, 100, 100, backgroundTransparency });

			m_background.setSize(m_outerDim);
			m_background.setPosition(m_topCentrePoint.x - m_outerDim.x / 2, m_topCentrePoint.y);
			// background position is based on its top left corner
	}


	/*StackMenu::StackMenu(StackMenu&& other)
		: m_widgets(std::move(other.m_widgets))
		, m_background(std::move(other.m_background))
		, m_basePosition(other.m_basePosition)
		, m_baseSize(other.m_baseSize) {}

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
		//m_topCentrePoint.y = m_origBasePositionY;
		m_drawingPos_y = m_topCentrePoint.y;
		m_outerDim.y = 0;
		m_background.setSize(m_outerDim);
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

	void StackMenu::hideOutline()
	{
		m_background.setOutlineColor(sf::Color::Transparent);
	}

	void StackMenu::showOutline()
	{
		m_background.setOutlineColor(m_origOutlineColour);
		//m_background.setOutlineThickness(1);
		//m_background.setPosition(m_topCentrePoint);// .x - m_outerDim.x / 2, m_topCentrePoint.y);
		
	}

	// TODO: update to adjust to the fact that the base size doesn't really need to adjust for the playing menu and options menu, only for
	// the main menu, since the playing menu base size is always the same height, but the main menu base size grows as buttons are added.
	void StackMenu::initWidget(Widget& widget)
	{
		// widgets must be added consecutively in the order they are to appear on-screen, reading left to right in rows from top to bottom of menu
		
		// xPos : is the x-coordinate of the top-centre point of a widget
		// n_ : factor to scale the horiz. distance between shapes (relative to the distance from outside border to shape)
		// a_ : uniform horizontal separation between shapes in columnStyle # of columns

		// for 2 circles/row: [whole row width = a + 2*rad + a*n + 2*rad + a]
		// for 3 circles/row: [whole row width = a + 2*rad + a*n + 2*rad + a*n + 2*rad + a]

		float drawingPos_x = 0; //this initialization value is meaningless
		float n_ = 0.8f;
		float a_ = (m_outerDim.x - widget.getMaxNumInRow() * widget.getSize().x) / (2.f + (float)(widget.getMaxNumInRow() - 1) * n_);

		if (m_bIsFirstWidgetInMenu)
		{
			m_bIsFirstWidgetInMenu = false;

			m_drawingPos_y += m_widgetSpacer; // first widget will appear at a small gap under the top border
			m_outerDim.y += widget.getSize().y + m_widgetSpacer * 2; // expand the base from 0 to widgetSize + 2*space
			m_background.setSize(m_outerDim);

			switch (widget.getMaxNumInRow())
			{
			case 1:
				drawingPos_x = m_topCentrePoint.x; // centre of row
				break;
			case 2:
				drawingPos_x = m_topCentrePoint.x - n_ * a_ / 2.f - widget.getSize().x / 2.f; // x-coord of centre of left-most drawing position
				break;
			case 3:
				drawingPos_x = m_topCentrePoint.x - widget.getSize().x - a_ * n_; // x-coord of centre of left-most drawing position
				break;
			}
			// widgets have their origin at their centre
			widget.setPosition({ drawingPos_x, m_drawingPos_y + widget.getSize().y / 2 });
			widget.setPositionInRow(0);
		}
		else
		{
			if ((widget.getMaxNumInRow() != m_widgets.back()->getMaxNumInRow()) || // new widget has different row layout than last widget
				(m_widgets.back()->getMaxNumInRow() == m_widgets.back()->getPositionInRow() + 1)) // last widget completed a row
			{
				m_drawingPos_y += m_widgets.back()->getSize().y + m_widgetSpacer;
				m_outerDim.y += widget.getSize().y + m_widgetSpacer;
				m_background.setSize(m_outerDim);
			}
			switch (widget.getMaxNumInRow())
			{
			case 1:
				drawingPos_x = m_topCentrePoint.x; // centre of row
				widget.setPositionInRow(0);
				break;

			case 2:
				//specific form for a_ = 2 : a_ = (m_baseSize.x - 2.f * widget.getSize().x) / (2.f + n_);

				if (m_widgets.back()->getMaxNumInRow() == 2 && m_widgets.back()->getPositionInRow() == 0)
				{
					drawingPos_x = m_topCentrePoint.x + n_ * a_ / 2.f + widget.getSize().x / 2.f; // (top-centre of) right circle
					widget.setPositionInRow(1);
				}
				else // this will be the first (left-most) object in the a new row
				{
					drawingPos_x = m_topCentrePoint.x - n_ * a_ / 2.f - widget.getSize().x / 2.f; // (top-centre of) left circle
					widget.setPositionInRow(0);
				}

				break;

			case 3:
				//specific form for a_ = 3 : a_ = (m_baseSize.x - 3.f * widget.getSize().x) / (2.f + 2.f * n_);

				if (m_widgets.back()->getMaxNumInRow() == 3 && m_widgets.back()->getPositionInRow() == 1)
				{// prev widget was placed in middle spot
					drawingPos_x = m_topCentrePoint.x + widget.getSize().x + a_ * n_; // (top-centre of) right-most spot
					widget.setPositionInRow(2);
				}
				else if (m_widgets.back()->getMaxNumInRow() == 3 && m_widgets.back()->getPositionInRow() == 0)
				{// prev widget was placed in left-most spot
					drawingPos_x = m_topCentrePoint.x; // (top-centre of) middle circle
					widget.setPositionInRow(1);
				}
				else
				{// last widget either had a different "max num in row" scheme, or was placed in the right-most spot (finishing the row)
					drawingPos_x = m_topCentrePoint.x - widget.getSize().x - a_ * n_; // (top-centre of) left-most spot
					widget.setPositionInRow(0);
				}
				break;
			}
			widget.setPosition({ drawingPos_x, m_drawingPos_y + widget.getSize().y / 2 });
		}
	}

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
		for (unsigned int i = 0; i < m_widgets.size(); i++)
		{
			m_widgets.at(i)->render(renderer);
		}
	}
}



