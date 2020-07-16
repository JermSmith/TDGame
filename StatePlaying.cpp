#include "StatePlaying.h"
#include "StateMainMenu.h"
#include "Game.h"

#include "Util\Math.h"
#include "Util\Random.h"

#include <iostream>

StatePlaying::StatePlaying(Game& game) : StateBase(game)
	,
	m_worldManager(game.getWindow())
	,
	m_playingMenu(sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 485)
		, (float)sizes::PLAYINGMENU_X
		, -2.f, 155, graphics::DEFAULTMENU_SPACER)
	,
	m_towersMenu(sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 0)
		, (float)sizes::PLAYINGMENU_X
		, -2.f, 155, graphics::DEFAULTMENU_SPACER)
	,
	m_optionsMenu(sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 217)
		, (float)sizes::PLAYINGMENU_X
		, -2.f, 155, graphics::DEFAULTMENU_SPACER)
	,
	m_confirmExitMenu(sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 380)
		, (float)sizes::PLAYINGMENU_X
		, -2.f, 155, graphics::DEFAULTMENU_SPACER)
	,
	m_confirmResetGameMenu(sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 380)
		, (float)sizes::PLAYINGMENU_X
		, -2.f, 155, graphics::DEFAULTMENU_SPACER)
	,
	m_prevWaveStatsMenu(sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 217)
		, (float)sizes::PLAYINGMENU_X
		, -2.f, 155, graphics::DEFAULTMENU_SPACER)
{
	m_worldManager.reset();
	m_worldManager.createRandomPath(0);
	generateWidgets(game);
	m_populatePlayingMenu();
	m_populateTowersMenu();

	m_optionsMenu.hide();
	m_confirmExitMenu.hide();
	m_confirmResetGameMenu.hide();
	m_prevWaveStatsMenu.hide();

	m_musicFilenames = { "Chan_Wai_Fat_-_05_-_Dream_instrumental" , "Lee_Rosevere_-_09_-_Compassion_keys_version" , 
	"Chad_Crouch_-_Algorithms" , "Kai_Engel_-_04_-_Moonlight_Reprise", "Koona_-_02_-_Starkey" , 
	"Lee_Rosevere_-_12_-_Dont_Trust_the_Cloud", "Lee_Rosevere_-_13_-_All_I_Have_Left_Are_These_Photographs", 
	"Lee_Rosevere_-_15_-_Where_Was_I", "Lee_Rosevere_-_16_-_The_Little_Painter_Man", 
	"Lee_Rosevere_-_17_-_We_Dont_Know_How_it_Ends", "Obsibilo_-_03_-_Soixante-8", "Podington_Bear_-_Starling"};

	m_backgroundTexture = ResourceHolder::get().textures.get("space");
	m_backgroundTexture.setRepeated(true);
	m_backgroundSpriteLeft.setTexture(m_backgroundTexture);
	m_backgroundSpriteRight.setTexture(m_backgroundTexture);

	m_backgroundSpriteLeft.setScale((float)sizes::WORLD_SIZE_Y / (float)m_backgroundTexture.getSize().y,
		(float)sizes::WORLD_SIZE_Y / (float)(m_backgroundTexture.getSize().y));
	m_backgroundSpriteRight.setScale((float)sizes::WORLD_SIZE_Y / (float)m_backgroundTexture.getSize().y,
		(float)sizes::WORLD_SIZE_Y / (float)(m_backgroundTexture.getSize().y));

	m_backgroundSpriteRight.setPosition(
		(float)sizes::WORLD_SIZE_Y / (float)m_backgroundTexture.getSize().y * (float)m_backgroundTexture.getSize().x, 0);
}

void StatePlaying::handleEvent(sf::Event e)
{
	m_worldManager.handleEvent(e, m_pGame->getWindow());

	auto clickPos = m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow()));
	switch (e.type)
	{
	case sf::Event::MouseButtonPressed:
		switch (e.mouseButton.button)
		{
		case sf::Mouse::Left:
			if (m_towersMenu.bClickedInMenu(clickPos))
			{
				m_confirmExitMenu.hide();
				m_confirmResetGameMenu.hide();
				m_optionsMenu.hide();
				m_prevWaveStatsMenu.hide();
			}
			else if (m_playingMenu.bClickedInMenu(clickPos))
			{
				m_worldManager.setbTowerBeingPlaced(false);
			}
			break;
		}
	}

	m_playingMenu.handleEvent(e, m_pGame->getWindow());
	m_towersMenu.handleEvent(e, m_pGame->getWindow());
	m_optionsMenu.handleEvent(e, m_pGame->getWindow());
	m_confirmExitMenu.handleEvent(e, m_pGame->getWindow());
	m_confirmResetGameMenu.handleEvent(e, m_pGame->getWindow());
	m_prevWaveStatsMenu.handleEvent(e, m_pGame->getWindow());
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(const sf::RenderWindow& window)
{
	m_worldManager.update(window);

	m_playingMenu.update(window);
	m_towersMenu.update(window);
	m_optionsMenu.update(window);
	m_confirmExitMenu.update(window);
	m_confirmResetGameMenu.update(window);
	m_prevWaveStatsMenu.update(window);

	bnrNumLives.setText("Lives Remaining: " + std::to_string(m_worldManager.getNumLives()));
}

/*void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}*/

void StatePlaying::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_backgroundSpriteLeft);
	renderer.draw(m_backgroundSpriteRight);

	m_worldManager.render(renderer);

	m_playingMenu.render(renderer);
	m_towersMenu.render(renderer);
	m_optionsMenu.render(renderer);
	m_confirmExitMenu.render(renderer);
	m_confirmResetGameMenu.render(renderer);
	m_prevWaveStatsMenu.render(renderer);
}

void StatePlaying::generateWidgets(Game& game)
{
	// TODO: figure out where shop, inventory, etc. will be displayed

	btnPlaceTower1.setText("-1");
	btnPlaceTower1.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::subtract, 1, mousePos, 
					btnPlaceTower1.getPrimaryDim(), btnPlaceTower1.getPointCount());
			}
		});

	btnPlaceTower2.setText("+1");
	btnPlaceTower2.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::subtract, -1, mousePos, 
					btnPlaceTower2.getPrimaryDim(), btnPlaceTower2.getPointCount());
			}
		});

	btnPlaceTower3.setText("/2");
	btnPlaceTower3.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 2, mousePos, 
					btnPlaceTower3.getPrimaryDim(), btnPlaceTower3.getPointCount());
			}
		});

	btnPlaceTower4.setText("/3");
	btnPlaceTower4.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 3, mousePos, 
					btnPlaceTower4.getPrimaryDim(), btnPlaceTower4.getPointCount());
			}
		});

	btnPlaceTower5.setText("/5");
	btnPlaceTower5.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 5, mousePos, 
					btnPlaceTower5.getPrimaryDim(), btnPlaceTower5.getPointCount());
			}
		});

	btnPlaceTower6.setText("/7");
	btnPlaceTower6.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 7, mousePos, 
					btnPlaceTower6.getPrimaryDim(), btnPlaceTower6.getPointCount());
			}
		});

	btnPlaceTower7.setText("/11");
	btnPlaceTower7.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 11, mousePos, 
					btnPlaceTower7.getPrimaryDim(), btnPlaceTower7.getPointCount());
			}
		});

	btnPlaceTower8.setText("sqrt");
	btnPlaceTower8.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::root, 2, mousePos, 
					btnPlaceTower8.getPrimaryDim(), btnPlaceTower8.getPointCount());
			}
		});

	btnPlaceTower9.setText("cbrt");
	btnPlaceTower9.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::root, 3, mousePos, 
					btnPlaceTower9.getPrimaryDim(), btnPlaceTower9.getPointCount());
			}
		});

	btnStartWave.setText("Start Next Wave");
	btnStartWave.setFunction([&]()
		{
			m_worldManager.requestStartWave();
		});

	btnPrevWaveStats.setText("Previous Wave Stats");
	btnPrevWaveStats.setFunction([&]()
		{
			m_optionsMenu.hide();
			m_confirmExitMenu.hide();
			m_confirmResetGameMenu.hide();

			if (m_prevWaveStatsMenu.bContainsWidgets()) { m_prevWaveStatsMenu.hide(); }
			else { m_populatePrevWaveStatsMenu(); }
		});

	btnOptions.setText("Options");
	btnOptions.setFunction([&]()
		{
			m_confirmExitMenu.hide();
			m_confirmResetGameMenu.hide();
			m_prevWaveStatsMenu.hide();

			if (m_optionsMenu.bContainsWidgets()) { m_optionsMenu.hide(); }
			else { m_populateOptionsMenu(); }
			// TODO: implement options (music, colour scheme/graphics theme, game speed, etc.)
		});

	btnMainMenu.setText("Main Menu");
	btnMainMenu.setFunction([&]()
		{
			m_confirmResetGameMenu.hide();
			m_optionsMenu.hide();
			m_prevWaveStatsMenu.hide();
			
			if (m_confirmExitMenu.bContainsWidgets()) { m_confirmExitMenu.hide(); }
			else { m_populateConfirmExitMenu(); }
		});

	btnSaveGame.setText("Save Game");
	btnSaveGame.setFunction([&]()
		{
			// TODO: save game
		});

	btnRestartGame.setText("Reset game");
	btnRestartGame.setFunction([&]()
		{
			m_confirmExitMenu.hide();
			m_optionsMenu.hide();
			m_prevWaveStatsMenu.hide();

			if (m_confirmResetGameMenu.bContainsWidgets()) { m_confirmResetGameMenu.hide(); }
			else { m_populateConfirmResetGameMenu(); }
		});

	bnrNumLives.setText("Lives Remaining: " + std::to_string(m_worldManager.getNumLives()));

	// OPTIONS MENU

	btnToggleMusic.setText("Toggle Music");
	btnToggleMusic.setFunction([&]()
		{
			// TODO: add toggle music functionality
		});

	btnToggleColourScheme.setText("Toggle Colour Scheme");
	btnToggleColourScheme.setFunction([&]()
		{
			// TODO: add toggle colour scheme functionality
		});

	// CONFIRM EXIT MENU

	bnrExitPrompt.setText("Really want to leave?");

	btnYesExit.setText("Confirm Exit");
	btnYesExit.setFunction([&]()
		{
			game.pushState<StateMainMenu>(game);
		});

	btnNoDontExit.setText("Cancel");
	btnNoDontExit.setFunction([&]()
		{
			m_confirmExitMenu.hide();
		});

	// CONFIRM RESET GAME MENU

	bnrResetPrompt.setText("Really want to reset?");

	btnYesReset.setText("Confirm Reset");
	btnYesReset.setFunction([&]()
		{
			m_worldManager.reset();

			static Random<> rand;
			int rand50 = rand.getIntInRange(0, 1);
			switch (rand50)
			{
			case 0:
				m_worldManager.createRandomPath(0);
				break;
			case 1:
				m_worldManager.createOrthoPath(0);
				break;
			}

			m_confirmResetGameMenu.hide();
		});

	btnNoDontReset.setText("Cancel");
	btnNoDontReset.setFunction([&]()
		{
			m_confirmResetGameMenu.hide();
		});

	// PREV WAVE STATS

	bnrPrevWaveStat1.setText("Stat 1: ");
	bnrPrevWaveStat2.setText("Stat 2: ");
	bnrPrevWaveStat3.setText("Stat 3: ");

}

void StatePlaying::m_populatePlayingMenu()
{
	m_playingMenu.addWidget(btnStartWave);
	m_playingMenu.addWidget(btnPrevWaveStats);
	m_playingMenu.addWidget(btnOptions);
	m_playingMenu.addWidget(btnMainMenu);
	m_playingMenu.addWidget(btnSaveGame);
	m_playingMenu.addWidget(btnRestartGame);
	m_playingMenu.addWidget(bnrNumLives);
}

void StatePlaying::m_populateTowersMenu()
{
	m_towersMenu.addWidget(btnPlaceTower1);
	m_towersMenu.addWidget(btnPlaceTower2);
	m_towersMenu.addWidget(btnPlaceTower3);
	m_towersMenu.addWidget(btnPlaceTower4);
	m_towersMenu.addWidget(btnPlaceTower5);
	m_towersMenu.addWidget(btnPlaceTower6);
	m_towersMenu.addWidget(btnPlaceTower7);
	m_towersMenu.addWidget(btnPlaceTower8);
	m_towersMenu.addWidget(btnPlaceTower9);
}

void StatePlaying::m_populateOptionsMenu()
{
	m_optionsMenu.addWidget(btnToggleMusic);
	m_optionsMenu.addWidget(btnToggleColourScheme);

	m_optionsMenu.showOutline();
}

void StatePlaying::m_populateConfirmExitMenu()
{
	m_confirmExitMenu.addWidget(bnrExitPrompt);
	m_confirmExitMenu.addWidget(btnYesExit);
	m_confirmExitMenu.addWidget(btnNoDontExit);

	m_confirmExitMenu.showOutline();
}

void StatePlaying::m_populateConfirmResetGameMenu()
{
	m_confirmResetGameMenu.addWidget(bnrResetPrompt);
	m_confirmResetGameMenu.addWidget(btnYesReset);
	m_confirmResetGameMenu.addWidget(btnNoDontReset);

	m_confirmResetGameMenu.showOutline();
}

void StatePlaying::m_populatePrevWaveStatsMenu()
{
	m_prevWaveStatsMenu.addWidget(bnrPrevWaveStat1);
	m_prevWaveStatsMenu.addWidget(bnrPrevWaveStat2);
	m_prevWaveStatsMenu.addWidget(bnrPrevWaveStat3);

	m_prevWaveStatsMenu.showOutline();
}



