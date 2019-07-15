#include "StateMainMenu.h"
#include "StatePlaying.h"

#include "GUI\Button.h"
#include "GUI\Textbox.h"
#include "Game.h"

//#include <iostream>

StateMainMenu::StateMainMenu(Game& game)
	: StateBase(game)
	, m_mainMenu(game.getWindow(), 100)
{
	//m_banner.setSize(sf::Vector2f((float)128, (float)8));
	//m_banner.setPosition(sf::Vector2f(128, 64));
	//m_banner.setFillColor(sf::Color::White);

	auto btnNewGame = gui::makeButton();
	btnNewGame->setText("New Game");
	btnNewGame->setFunction([&]()
	{
		game.pushState<StatePlaying>(game);
	});
	
	auto btnLoadGame = gui::makeButton();
	btnLoadGame->setText("Load Game");
	btnLoadGame->setFunction([&]()
	{
		
	});

	auto btnOptions = gui::makeButton();
	btnOptions->setText("Options");
	btnOptions->setFunction([&]()
	{

	});

	auto btnHowToPlay = gui::makeButton();
	btnHowToPlay->setText("How To Play");
	btnHowToPlay->setFunction([&]()
	{

	});

	auto btnHighScores = gui::makeButton();
	btnHighScores->setText("High Scores");
	btnHighScores->setFunction([&]()
	{

	});

	auto btnExit = gui::makeButton();
	btnExit->setText("Exit");
	btnExit->setFunction([&]()
	{
		game.exitGame();
	});

	m_mainMenu.addWidget(std::move(btnNewGame));
	m_mainMenu.addWidget(std::move(btnLoadGame));
	m_mainMenu.addWidget(std::move(btnOptions));
	m_mainMenu.addWidget(std::move(btnHowToPlay));
	m_mainMenu.addWidget(std::move(btnHighScores));
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