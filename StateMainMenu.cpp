#include "StateMainMenu.h"
#include "StatePlaying.h"

#include "GUI\Button.h"
//#include "GUI\Textbox.h"
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

	//m_banner.setSize(sf::Vector2f((float)128, (float)8));
	//m_banner.setPosition(sf::Vector2f(128, 64));
	//m_banner.setFillColor(sf::Color::White);
}

void StateMainMenu::handleEvent(sf::Event e)
{
	m_mainMenu.handleEvent(e, m_pGame->getWindow());
	m_optionsMenu.handleEvent(e, m_pGame->getWindow());
}

void StateMainMenu::handleInput()
{

}

void StateMainMenu::update()
{
	
}

void StateMainMenu::render(sf::RenderTarget& renderer)
{
	m_mainMenu.render(renderer);
	m_optionsMenu.render(renderer);
	//renderer.draw(m_banner);
}

void StateMainMenu::generateButtons(Game& game)
{
	auto btnNewGame = gui::makeRectangularButton(gui::ButtonSize::Wide);
	btnNewGame->setText("New Game");
	btnNewGame->setFunction([&]()
	{
		game.pushState<StatePlaying>(game);
	});

	auto btnLoadGame = gui::makeRectangularButton(gui::ButtonSize::Wide);
	btnLoadGame->setText("Load Game");
	btnLoadGame->setFunction([&]()
	{

	});

	auto btnOptions = gui::makeRectangularButton(gui::ButtonSize::Wide);
	btnOptions->setText("Options");
	btnOptions->setFunction([&]()
	{
		if (!m_optionsMenu.bContainsWidgets()) { m_generateOptionsButtons(game); }
		else { m_optionsMenu.clearWidgets(); }
	});

	auto btnHowToPlay = gui::makeRectangularButton(gui::ButtonSize::Wide);
	btnHowToPlay->setText("How To Play");
	btnHowToPlay->setFunction([&]()
	{

	});

	auto btnHighScores = gui::makeRectangularButton(gui::ButtonSize::Wide);
	btnHighScores->setText("High Scores");
	btnHighScores->setFunction([&]()
	{

	});

	auto btnExit = gui::makeRectangularButton(gui::ButtonSize::Wide);
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

void StateMainMenu::m_generateOptionsButtons(Game& game)
{
	auto btnToggleMusic = gui::makeRectangularButton(gui::ButtonSize::Wide);
	btnToggleMusic->setText("Toggle Music");
	btnToggleMusic->setFunction([&]()
	{
		if (game.getMusicRequestStatus())
		{
			game.setMusicRequestStatus(false);
		}
		else
		{
			game.setMusicRequestStatus(true);
		}
	});

	auto btnColourScheme = gui::makeRectangularButton(gui::ButtonSize::Wide);
	btnColourScheme->setText("Toggle Change Colour Scheme");
	btnColourScheme->setFunction([&]()
	{

	});

	auto btnMainMenu = gui::makeRectangularButton(gui::ButtonSize::Wide);
	btnMainMenu->setText("Return to Menu");
	btnMainMenu->setFunction([&]()
	{
		m_optionsMenu.clearWidgets();
	});


	m_optionsMenu.addWidget(std::move(btnToggleMusic));
	m_optionsMenu.addWidget(std::move(btnColourScheme));
	m_optionsMenu.addWidget(std::move(btnMainMenu));
}

