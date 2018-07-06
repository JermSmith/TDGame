#include "StateMainMenu.h"
#include "StatePlaying.h"

#include "GUI\Button.h"
#include "GUI\Textbox.h"
#include "Game.h"

#include <iostream>

StateMainMenu::StateMainMenu(Game& game) : StateBase(game), m_mainMenu(game.getWindow(), 50)
{
	m_banner.setSize(sf::Vector2f((float)128, (float)8));
	m_banner.setPosition(sf::Vector2f(128, 64));
	m_banner.setFillColor(sf::Color::White);

	auto playBtn = gui::makeButton();
	playBtn->setText("Play");
	playBtn->setFunction([&]()
	{
		std::cout << "Play Button clicked!" << std::endl;
		game.pushState<StatePlaying>(game);
	});
	m_mainMenu.addWidget(std::move(playBtn));
	
	auto btn2 = gui::makeButton();
	btn2->setText("Button 2");
	btn2->setFunction([&]()
	{
		std::cout << "Button 2 clicked!" << std::endl;
	});
	m_mainMenu.addWidget(std::move(btn2));

	auto exitBtn = gui::makeButton();
	exitBtn->setText("Exit");
	exitBtn->setFunction([&]()
	{
		std::cout << "Exit Button clicked!" << std::endl;
		game.exitGame();
	});
	m_mainMenu.addWidget(std::move(exitBtn));
}

void StateMainMenu::handleEvent(sf::Event e)
{
	m_mainMenu.handleEvent(e, m_pGame->getWindow());
}

void StateMainMenu::handleInput()
{

}

void StateMainMenu::update(sf::Time deltaTime)
{

}

void StateMainMenu::render(sf::RenderTarget& renderer)
{
	m_mainMenu.render(renderer);
	renderer.draw(m_banner);
}