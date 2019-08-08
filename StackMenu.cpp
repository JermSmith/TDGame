#include "StackMenu.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"

constexpr float BASE_Y = 95.0f;

namespace gui
{
	StackMenu::StackMenu(const sf::RenderWindow& window, float baseY)//this constructor is called each time the main menu is made
		: m_basePosition((float)sizes::WORLD_SIZE_X / 2.0f, baseY)
		, m_baseSize(300, 20)
	{
		m_background.setOutlineThickness(2);
		m_background.setOutlineColor(sf::Color::Green);
		m_background.setFillColor({ 100, 100, 100, 230 });
		m_background.setSize(m_baseSize);
		m_background.setPosition(m_basePosition.x - m_baseSize.x / 2, m_basePosition.y - WIDGET_SPACER);

		m_titleText.setPosition(0, m_basePosition.y - 35);
		m_titleText.setOutlineColor(sf::Color::Black);
		m_titleText.setOutlineThickness(1);
		m_titleText.setCharacterSize(30);
	}

	StackMenu::StackMenu(const sf::Vector2f& basePosition, const sf::Vector2f& baseSize) //this constructor is called each time the playing menu is made
		: m_basePosition(basePosition), m_baseSize(baseSize)
	{
		m_background.setFillColor({ 100, 100, 100, 128 });
		m_background.setSize(m_baseSize);
		m_background.setPosition(m_basePosition.x - m_baseSize.x / 2, m_basePosition.y - WIDGET_SPACER); // explains the space above the first widget
		// background position is based on its top left corner
	}

	StackMenu::StackMenu(StackMenu&& other)
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
	}

	void StackMenu::addWidget(std::unique_ptr<Widget> w)
	{
		initWidget(*w);
		m_widgets.push_back(std::move(w));
	}

	void StackMenu::initWidget(Widget& widget)
	{
		// if n widgets are to be represented in a grid, they must be added consecutively
		int numColumns = widget.getNumColumns();
		
		float xPos;

		// factor to scale the middle space between two shapes
		float n_ = 0.8f; 

		// constant horizontal separation between shapes in columns
		float a_ = (m_baseSize.x - numColumns * widget.getSize().x) / (2.f + (float)(numColumns - 1) * n_);

		// for 2 circles: [whole width = a + 2*radius + a*n + 2*radius + a]
		// for 3 circles: [whole width = a + 2*rad + a*n + 2*rad + a*n + 2*rad + a]

		switch (numColumns)
		{
		case 1:
			m_consecutiveColumnStyleCount = 0;
			
			widget.setPosition({ m_basePosition.x, m_basePosition.y + widget.getSize().y / 2 }); // applies for rectangles having origin at centre
			
			m_prevNumColumns = 1;
			break;

		case 2:
			//specific form for a_ : a_ = (m_baseSize.x - 2 * widget.getSize().x) / (2.f + n_);

			if (m_prevNumColumns == 2)
			{
				m_consecutiveColumnStyleCount = (m_consecutiveColumnStyleCount + 1) % 2; // increase the consecutive call count, but 2 resets to 0
			}
			else
			{
				m_consecutiveColumnStyleCount = 0; // previous call was not for a 2-column object
			}

			switch (m_consecutiveColumnStyleCount)
			{
			case 0:
				xPos = m_basePosition.x - n_ * a_ / 2.f - widget.getSize().x / 2.f; // left circle
				break;

			case 1:
				xPos = m_basePosition.x + n_ * a_ / 2.f + widget.getSize().x / 2.f; // right circle
				break;
			}

			widget.setPosition({ xPos, m_basePosition.y + widget.getSize().y / 2 });

			m_prevNumColumns = 2;
			break;

		case 3:
			//specific form for a_ : a_ = (m_baseSize.x - 3.f * widget.getSize().x) / (2.f + 2.f * n_);

			if (m_prevNumColumns == 3)
			{
				m_consecutiveColumnStyleCount = (m_consecutiveColumnStyleCount + 1) % 3; // increase the consecutive call count, but 3 resets to 0
			}
			else
			{
				m_consecutiveColumnStyleCount = 0; // previous call was not for a 3-column object
			}

			switch (m_consecutiveColumnStyleCount)
			{
			case 0:
				xPos = m_basePosition.x - widget.getSize().x - a_ * n_; // left circle
				break;

			case 1:
				xPos = m_basePosition.x; // middle circle
				break;

			case 2:
				xPos = m_basePosition.x + widget.getSize().x + a_ * n_; // right circle
				break;
			}

			widget.setPosition({ xPos, m_basePosition.y + widget.getSize().y / 2 });

			m_prevNumColumns = 3;
			break;
		}

		if (m_consecutiveColumnStyleCount == numColumns - 1) // inserted the final shape to complete a row
		{
			m_basePosition.y += widget.getSize().y + WIDGET_SPACER; // account for widget that was just added, plus spacing
			m_baseSize.y += widget.getSize().y + WIDGET_SPACER;
			m_background.setSize(m_baseSize);
		}

	}

	void StackMenu::setTitle(const std::string& title)
	{
		m_titleText.setString(title);
		m_titleText.setPosition(getWindow().getSize().x - m_titleText.getGlobalBounds().width / 2, m_titleText.getPosition().y);
	}

	void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
	{
		for (auto& widget : m_widgets)
		{
			widget->handleEvent(e, window);
		}
	}

	void StackMenu::render(sf::RenderTarget& renderer)
	{
		renderer.draw(m_background);
		renderer.draw(m_titleText);
		for (auto& widget : m_widgets)
		{
			widget->render(renderer);
		}
	}

	const sf::RenderWindow& StackMenu::getWindow() const
	{
		return *m_pWindow;
	}

}