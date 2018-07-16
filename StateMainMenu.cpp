#include "StateMainMenu.h"
#include "StatePlaying.h"

#include "GUI\Button.h"
#include "GUI\Textbox.h"
#include "Game.h"

//#include <iostream>

StateMainMenu::StateMainMenu(Game& game)
	: StateBase(game), m_mainMenu(game.getWindow(), 50)
{
	m_banner.setSize(sf::Vector2f((float)128, (float)8));
	m_banner.setPosition(sf::Vector2f(128, 64));
	m_banner.setFillColor(sf::Color::White);

	auto btnPlay = gui::makeButton();
	btnPlay->setText("Play");
	btnPlay->setFunction([&]()
	{
		game.pushState<StatePlaying>(game);
	});
	
	auto btn2 = gui::makeButton();
	btn2->setText("Button 2");
	btn2->setFunction([&]()
	{
		
	});

	auto btnExit = gui::makeButton();
	btnExit->setText("Exit");
	btnExit->setFunction([&]()
	{
		game.exitGame();
	});

	m_mainMenu.addWidget(std::move(btnPlay));
	m_mainMenu.addWidget(std::move(btn2));
	m_mainMenu.addWidget(std::move(btnExit));
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