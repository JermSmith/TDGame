#include "StatePlaying.h"
#include "StateMainMenu.h"
#include "Game.h"

#include "Util\Math.h"
#include "Util\Random.h"

#include <iostream>

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
	, m_playingMenu(0)
{
	m_worldManager.reset();
	m_worldManager.createRandomPath(0);
	generateButtons(game);

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
	m_playingMenu.handleEvent(e, m_pGame->getWindow());
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(const sf::RenderWindow& window)
{
	m_worldManager.update(window);

	bnrNumLives.setText("Lives Remaining: " + std::to_string(m_worldManager.getNumLives()));

	for (auto& b : m_playingMenu.getWidgets())
	{
		b->update(window);
	}

	//if (m_bGameOver)
	//{
		// do something to end the game
	//}
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
}

void StatePlaying::generateButtons(Game& game)
{
	// TODO: figure out where wave stats, tower stats, shop, inventory, etc. will be displayed

	btnStartWave.setText("Start Next Wave");
	btnStartWave.setFunction([&]()
		{
			m_worldManager.requestStartWave();
		});

	btnPlaceTower1.setText("-1");
	btnPlaceTower1.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(game.getWindow().mapPixelToCoords(sf::Mouse::getPosition(game.getWindow())));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::subtract, 1, mousePos, btnPlaceTower1.getPrimaryDim());
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
				m_worldManager.getDummyTower()->setBasicProperties(attackType::subtract, -1, mousePos, btnPlaceTower2.getPrimaryDim());
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
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 2, mousePos, btnPlaceTower3.getPrimaryDim());
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
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 3, mousePos, btnPlaceTower4.getPrimaryDim());
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
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 5, mousePos, btnPlaceTower5.getPrimaryDim());
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
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 7, mousePos, btnPlaceTower6.getPrimaryDim());
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
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 11, mousePos, btnPlaceTower7.getPrimaryDim());
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
				m_worldManager.getDummyTower()->setBasicProperties(attackType::root, 2, mousePos, btnPlaceTower8.getPrimaryDim());
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
				m_worldManager.getDummyTower()->setBasicProperties(attackType::root, 3, mousePos, btnPlaceTower9.getPrimaryDim());
			}
		});

	btnPrevWaveStats.setText("Previous Wave Stats");
	btnPrevWaveStats.setFunction([&]()
		{

		});

	btnOptions.setText("Options");
	btnOptions.setFunction([&]()
		{
			// include here toggle music, colour scheme, ...
		});

	btnMainMenu.setText("Main Menu");
	btnMainMenu.setFunction([&]()
		{
			game.pushState<StateMainMenu>(game);
		});

	btnRestartGame.setText("Reset game");
	btnRestartGame.setFunction([&]()
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

		});

	bnrNumLives.setText("Lives Remaining: " + std::to_string(m_worldManager.getNumLives()));

	m_playingMenu.addWidget(btnStartWave);
	m_playingMenu.addWidget(btnPlaceTower1);
	m_playingMenu.addWidget(btnPlaceTower2);
	m_playingMenu.addWidget(btnPlaceTower3);
	m_playingMenu.addWidget(btnPlaceTower4);
	m_playingMenu.addWidget(btnPlaceTower5);
	m_playingMenu.addWidget(btnPlaceTower6);
	m_playingMenu.addWidget(btnPlaceTower7);
	m_playingMenu.addWidget(btnPlaceTower8);
	m_playingMenu.addWidget(btnPlaceTower9);
	m_playingMenu.addWidget(btnPrevWaveStats);
	m_playingMenu.addWidget(btnOptions);
	m_playingMenu.addWidget(btnMainMenu);
	m_playingMenu.addWidget(btnRestartGame);
	m_playingMenu.addWidget(bnrNumLives);

}


