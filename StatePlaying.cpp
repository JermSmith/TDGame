#include "StatePlaying.h"
#include "StateMainMenu.h"

#include "Util\Random.h"
#include "Util\Math.h"
#include "Game.h"

#include <iostream>

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
	, m_playingMenu(0)// sf::Vector2f(((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2), 0),
		//sf::Vector2f((float)sizes::PLAYINGMENU_X, 0))
{
	m_musicFilenames = { "Chan_Wai_Fat_-_05_-_Dream_instrumental" , "Lee_Rosevere_-_09_-_Compassion_keys_version" };

	generateButtons(game);	

	m_world.createRandomPath(0);

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
	m_playingMenu.handleEvent(e, m_pGame->getWindow());
	m_world.handleEvent(e, m_pGame->getWindow());
	
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update()
{
	m_world.update(m_pGame->getWindow());

	//m_playingMenu.updateWidgetText(bnrNumLives->getPositionInMenu(), "Lives Remaining: " + std::to_string(m_world.getNumLives()));

	bnrNumLives.setText("Lives Remaining: " + std::to_string(m_world.getNumLives()));

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

	m_playingMenu.render(renderer);

	m_world.render(renderer);
}

void StatePlaying::generateButtons(Game& game)
{
	btnStartWave.setText("Start Next Wave");
	btnStartWave.setFunction([&]()
	{
		m_world.requestStartWave();
	});

	btnPlaceTower1.setText("-1");
	btnPlaceTower1.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::subtract, 1, mousePos);
		}
	});

	
	btnPlaceTower2.setText("+1");
	btnPlaceTower2.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::subtract, -1, mousePos);
		}
	});

	btnPlaceTower3.setText("/2");
	btnPlaceTower3.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::divide, 2, mousePos);
		}
	});

	btnPlaceTower4.setText("/3");
	btnPlaceTower4.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::divide, 3, mousePos);
		}
	});

	btnPlaceTower5.setText("/5");
	btnPlaceTower5.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::divide, 5, mousePos);
		}
	});

	btnPlaceTower6.setText("/7");
	btnPlaceTower6.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::divide, 7, mousePos);
		}
	});

	// TODO: figure out where wave stats, tower stats, shop, inventory, etc. will be displayed
	btnPlaceTower7.setText("/11");
	btnPlaceTower7.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::divide, 11, mousePos);
		}
	});

	btnPlaceTower8.setText("sqrt");
	btnPlaceTower8.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::root, 2, mousePos);
		}
	});
 
	btnPlaceTower9.setText("cbrt");
	btnPlaceTower9.setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			sf::Vector2f mousePos = sf::Vector2f(m_pGame->getWindow().mapPixelToCoords(sf::Mouse::getPosition(m_pGame->getWindow())));
			m_world.setdummyTowerProperties(attackType::root, 3, mousePos);
		}
	});

	btnPrevWaveStats.setText("Previous Wave Stats");
	btnPrevWaveStats.setFunction([&]()
	{

	});

	btnRestartGame.setText("Restart Game");
	btnRestartGame.setFunction([&]()
	{
		m_world.clearScene();

		static Random<> rand;
		int rand50 = rand.getIntInRange(0, 1);
		switch (rand50)
		{
		case 0:
			m_world.createRandomPath(0);
			break;
		case 1:
			m_world.createOrthoPath(0);
			break;
		}

	});

	btnMainMenu.setText("Main Menu");
	btnMainMenu.setFunction([&]()
	{
		game.pushState<StateMainMenu>(game);
	});

	btnToggleMusic.setText("Toggle Music");
	btnToggleMusic.setFunction([&]()
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

	bnrNumLives.setText("Lives Remaining: " + std::to_string(m_world.getNumLives()));

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
	m_playingMenu.addWidget(btnRestartGame);
	m_playingMenu.addWidget(btnMainMenu);
	m_playingMenu.addWidget(btnToggleMusic);
	m_playingMenu.addWidget(bnrNumLives);
	

	
}



