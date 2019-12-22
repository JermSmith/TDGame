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
	m_musicFilenames = { "Lee_Rosevere_-_12_-_Dont_Trust_the_Cloud" , "Kai_Engel_-_04_-_Moonlight_Reprise" };

	//m_banner.setSize(sf::Vector2f((float)128, (float)8));
	//m_banner.setPosition(sf::Vector2f(128, 64));
	//m_banner.setFillColor(sf::Color::White);

	auto btnNewGame = gui::makeButton(gui::ButtonSize::Wide);
	btnNewGame->setText("New Game");
	btnNewGame->setFunction([&]()
	{
		game.pushState<StatePlaying>(game);
	});
	
	auto btnLoadGame = gui::makeButton(gui::ButtonSize::Wide);
	btnLoadGame->setText("Load Game");
	btnLoadGame->setFunction([&]()
	{
		
	});

	auto btnOptions = gui::makeButton(gui::ButtonSize::Wide);
	btnOptions->setText("Options");
	btnOptions->setFunction([&]()
	{

	});

	auto btnHowToPlay = gui::makeButton(gui::ButtonSize::Wide);
	btnHowToPlay->setText("How To Play");
	btnHowToPlay->setFunction([&]()
	{

	});

	auto btnHighScores = gui::makeButton(gui::ButtonSize::Wide);
	btnHighScores->setText("High Scores");
	btnHighScores->setFunction([&]()
	{

	});

	auto btnExit = gui::makeButton(gui::ButtonSize::Wide);
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
	//renderer.draw(m_banner);
}

