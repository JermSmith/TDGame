#include "StateMainMenu.h"
#include "StatePlaying.h"

#include "Game.h"

//#include <iostream>

StateMainMenu::StateMainMenu(Game& game)
	: StateBase(game)
	//, m_mainMenu(game.getWindow(), 100)
	, m_mainMenu(game.getWindow(), 100)
	, m_optionsMenu(100)// sf::Vector2f(((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2), 0),
		//sf::Vector2f((float)sizes::PLAYINGMENU_X, 0))
{
	m_musicFilenames = { "Kai_Engel_-_04_-_Moonlight_Reprise" , "Lee_Rosevere_-_12_-_Dont_Trust_the_Cloud" };

	generateButtons(game);
}

void StateMainMenu::handleEvent(sf::Event e)
{
	m_mainMenu.handleEvent(e, m_pGame->getWindow());
	m_optionsMenu.handleEvent(e, m_pGame->getWindow());
}

void StateMainMenu::handleInput()
{

}

void StateMainMenu::update(const sf::RenderWindow& window)
{
	for (auto& b : m_mainMenu.getWidgets())
	{
		b->update(window);
	}
	for (auto& b : m_optionsMenu.getWidgets())
	{
		b->update(window);
	}
}

void StateMainMenu::render(sf::RenderTarget& renderer)
{
	m_mainMenu.render(renderer);
	m_optionsMenu.render(renderer);
}

void StateMainMenu::generateButtons(Game& game)
{
	btnNewGame.setText("New Game");
	btnNewGame.setFunction([&]()
	{
		game.pushState<StatePlaying>(game);
	});

	btnLoadGame.setText("Load Game");
	btnLoadGame.setFunction([&]()
	{

	});
	
	btnOptions.setText("Options");
	btnOptions.setFunction([&]()
	{
		if (!m_optionsMenu.bContainsWidgets()) { m_generateOptionsButtons(game); }
		else { m_optionsMenu.clearWidgets(); }
	});

	btnHowToPlay.setText("How To Play");
	btnHowToPlay.setFunction([&]()
	{

	});

	btnHighScores.setText("High Scores");
	btnHighScores.setFunction([&]()
	{

	});

	btnExit.setText("Exit");
	btnExit.setFunction([&]()
	{
		game.exitGame();
	});

	m_mainMenu.addWidget(btnNewGame);
	m_mainMenu.addWidget(btnLoadGame);
	m_mainMenu.addWidget(btnOptions);
	m_mainMenu.addWidget(btnHowToPlay);
	m_mainMenu.addWidget(btnHighScores);
	m_mainMenu.addWidget(btnExit);

}

void StateMainMenu::m_generateOptionsButtons(Game& game)
{
	btnToggleMusic.setText("Toggle Music");
	btnToggleMusic.setFunction([&]()
	{
		if (game.getMusicRequestStatus()) { game.setMusicRequestStatus(false); }
		else { game.setMusicRequestStatus(true); }
	});

	btnColourScheme.setText("Toggle Change Colour Scheme");
	btnColourScheme.setFunction([&]()
	{

	});

	btnMainMenu.setText("Return to Menu");
	btnMainMenu.setFunction([&]()
	{
		m_optionsMenu.clearWidgets();
	});

	m_optionsMenu.addWidget(btnToggleMusic);
	m_optionsMenu.addWidget(btnColourScheme);
	m_optionsMenu.addWidget(btnMainMenu);
}

