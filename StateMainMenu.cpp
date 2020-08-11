#include "StateMainMenu.h"
#include "StatePlaying.h"
#include "Game.h"

#include "Util\Matrix.h"
#include <iostream>

StateMainMenu::StateMainMenu(Game& game)
	: StateBase(game)
	, m_mainMenu(
		sf::Vector2f((float)sizes::WORLD_SIZE_X/ 2.0f, 100)
		, (float)sizes::MAINMENU_SIZE_X
		, 4.f, 255, graphics::DEFAULTMENU_SPACER)
	,
	m_optionsMenu(
		sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 0)
		, (float)sizes::PLAYINGMENU_X
		, 2.f, 255, graphics::DEFAULTMENU_SPACER)
{
	m_musicFilenames = { "Kai_Engel_-_04_-_Moonlight_Reprise", "Lee_Rosevere_-_09_-_Compassion_keys_version" ,
	"Chad_Crouch_-_Algorithms" , "Koona_-_02_-_Starkey" , "Chan_Wai_Fat_-_05_-_Dream_instrumental" ,
	"Lee_Rosevere_-_12_-_Dont_Trust_the_Cloud", "Lee_Rosevere_-_13_-_All_I_Have_Left_Are_These_Photographs",
	"Lee_Rosevere_-_15_-_Where_Was_I", "Lee_Rosevere_-_16_-_The_Little_Painter_Man",
	"Lee_Rosevere_-_17_-_We_Dont_Know_How_it_Ends", "Obsibilo_-_03_-_Soixante-8", "Podington_Bear_-_Starling" };

	generateWidgets(game);
	m_populateMainMenu();

	// MATRIX TESTING AREA

	Matrix matrix1({ { 1.5f, 10.7f, 22.68f, -40}, {1, 11, -1, 9.7}, {-1, -2, -3, -4}, {4.5f, -1, 1.1f, 5.2f} });
	std::cout << "matrix 1: " << std::endl;
	std::cout << std::to_string(matrix1(1, 1)) << ", ";
	std::cout << std::to_string(matrix1(1, 2)) << ", ";
	std::cout << std::to_string(matrix1(1, 3)) << ", ";
	std::cout << std::to_string(matrix1(1, 4)) << std::endl;
	std::cout << std::to_string(matrix1(2, 1)) << ", ";
	std::cout << std::to_string(matrix1(2, 2)) << ", ";
	std::cout << std::to_string(matrix1(2, 3)) << ", ";
	std::cout << std::to_string(matrix1(2, 4)) << std::endl;
	std::cout << std::to_string(matrix1(3, 1)) << ", ";
	std::cout << std::to_string(matrix1(3, 2)) << ", ";
	std::cout << std::to_string(matrix1(3, 3)) << ", ";
	std::cout << std::to_string(matrix1(3, 4)) << std::endl;
	std::cout << std::to_string(matrix1(4, 1)) << ", ";
	std::cout << std::to_string(matrix1(4, 2)) << ", ";
	std::cout << std::to_string(matrix1(4, 3)) << ", ";
	std::cout << std::to_string(matrix1(4, 4)) << std::endl << std::endl;

	std::cout << " matrix 1 determinant = " << std::to_string(matrix1.determinant()) << std::endl;

	/*
	Matrix matrix4({ { -5 }, { -0.5 } , { 0 } });
	std::cout << "matrix 4: " << std::endl;
	std::cout << std::to_string(matrix4(1, 1)) << std::endl;
	std::cout << std::to_string(matrix4(2, 1)) << std::endl;
	std::cout << std::to_string(matrix4(3, 1)) << std::endl << std::endl;

	Matrix matrix2({ { cosf(0.01), sinf(0.01), 0 }, { -1 * sinf(0.01), cosf(0.01), 0 }, { 0, 0, 1 } });

	Matrix matrix2Inverse = matrix2.inverse();

	std::cout << "matrix 2: " << std::endl;
	std::cout << std::to_string(matrix2(1, 1)) << ", ";
	std::cout << std::to_string(matrix2(1, 2)) << ", ";
	std::cout << std::to_string(matrix2(1, 3)) << std::endl;
	std::cout << std::to_string(matrix2(2, 1)) << ", ";
	std::cout << std::to_string(matrix2(2, 2)) << ", ";
	std::cout << std::to_string(matrix2(2, 3)) << std::endl;
	std::cout << std::to_string(matrix2(3, 1)) << ", ";
	std::cout << std::to_string(matrix2(3, 2)) << ", ";
	std::cout << std::to_string(matrix2(3, 3)) << std::endl << std::endl;

	std::cout << "matrix 2 determinant: " << std::to_string(matrix2.determinant()) << std::endl << std::endl;

	std::cout << std::to_string(matrix2Inverse(1, 1)) << ", ";
	std::cout << std::to_string(matrix2Inverse(1, 2)) << ", ";
	std::cout << std::to_string(matrix2Inverse(1, 3)) << std::endl;
	std::cout << std::to_string(matrix2Inverse(2, 1)) << ", ";
	std::cout << std::to_string(matrix2Inverse(2, 2)) << ", ";
	std::cout << std::to_string(matrix2Inverse(2, 3)) << std::endl;
	std::cout << std::to_string(matrix2Inverse(3, 1)) << ", ";
	std::cout << std::to_string(matrix2Inverse(3, 2)) << ", ";
	std::cout << std::to_string(matrix2Inverse(3, 3)) << std::endl << std::endl;
	*/
	/*
	Matrix matrix3({ {0, 1}, {4.6f, -5} });

	Matrix matrix3Trans = matrix3.transpose();
	Matrix matrix3Inverse = matrix3.inverse();

	std::cout << "matrix 3: " << std::endl;

	std::cout << std::to_string(matrix3(1, 1)) << ", ";
	std::cout << std::to_string(matrix3(1, 2)) << std::endl;
	std::cout << std::to_string(matrix3(2, 1)) << ", ";
	std::cout << std::to_string(matrix3(2, 2)) << std::endl << std::endl;

	std::cout << "matrix 3 determinant: " << std::to_string(matrix3.determinant()) << std::endl << std::endl;

	std::cout << "matrix 3 transpose: " << std::endl;

	std::cout << std::to_string(matrix3Trans(1, 1)) << ", ";
	std::cout << std::to_string(matrix3Trans(1, 2)) << std::endl;
	std::cout << std::to_string(matrix3Trans(2, 1)) << ", ";
	std::cout << std::to_string(matrix3Trans(2, 2)) << std::endl << std::endl;

	std::cout << "matrix 3 inverse: " << std::endl;

	std::cout << std::to_string(matrix3Inverse(1, 1)) << ", ";
	std::cout << std::to_string(matrix3Inverse(1, 2)) << std::endl;
	std::cout << std::to_string(matrix3Inverse(2, 1)) << ", ";
	std::cout << std::to_string(matrix3Inverse(2, 2)) << std::endl << std::endl;*/

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
	m_mainMenu.update(window);
	m_optionsMenu.update(window);
}

void StateMainMenu::render(sf::RenderTarget& renderer)
{
	m_mainMenu.render(renderer);
	m_optionsMenu.render(renderer);
}

void StateMainMenu::generateWidgets(Game& game)
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


