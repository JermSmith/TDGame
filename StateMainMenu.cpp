#include "StateMainMenu.h"
#include "StatePlaying.h"

#include "Game.h"

StateMainMenu::StateMainMenu(Game& game)
	: StateBase(game)
	, m_mainMenu(
		sf::Vector2f((float)sizes::WORLD_SIZE_X/ 2.0f, 100)
		, (float)sizes::MAINMENU_SIZE_X
		, true
	),
	m_optionsMenu(
		sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 0)
		, (float)sizes::PLAYINGMENU_X
		, false
	)
{
	m_musicFilenames = { "Kai_Engel_-_04_-_Moonlight_Reprise", "Lee_Rosevere_-_09_-_Compassion_keys_version" ,
	"Chad_Crouch_-_Algorithms" , "Koona_-_02_-_Starkey" , "Chan_Wai_Fat_-_05_-_Dream_instrumental" ,
	"Lee_Rosevere_-_12_-_Dont_Trust_the_Cloud", "Lee_Rosevere_-_13_-_All_I_Have_Left_Are_These_Photographs",
	"Lee_Rosevere_-_15_-_Where_Was_I", "Lee_Rosevere_-_16_-_The_Little_Painter_Man",
	"Lee_Rosevere_-_17_-_We_Dont_Know_How_it_Ends", "Obsibilo_-_03_-_Soixante-8", "Podington_Bear_-_Starling" };

	generateButtons(game);
	m_populateMainMenu();
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
	// MAIN MENU BUTTONS

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
		if (!m_optionsMenu.bContainsWidgets()) { m_populateOptionsMenu(); }
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


	// OPTIONS MENU BUTTONS

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
}

void StateMainMenu::m_populateMainMenu()
{
	m_mainMenu.addWidget(btnNewGame);
	m_mainMenu.addWidget(btnLoadGame);
	m_mainMenu.addWidget(btnOptions);
	m_mainMenu.addWidget(btnHowToPlay);
	m_mainMenu.addWidget(btnHighScores);
	m_mainMenu.addWidget(btnExit);
}

void StateMainMenu::m_populateOptionsMenu()
{
	m_optionsMenu.addWidget(btnToggleMusic);
	m_optionsMenu.addWidget(btnColourScheme);
	m_optionsMenu.addWidget(btnMainMenu);
}


