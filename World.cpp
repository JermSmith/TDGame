//#include "World.h"
//#include "Path.h"
//#include "Util\Random.h"

//World::World(const sf::RenderWindow& window) : m_playingMenu(0)
//{
//	m_worldManager.reset();
//	m_worldManager.createRandomPath(0);
//	generateButtons(window);
//}

// void World::clearScene()
//{
//	m_worldManager.reset();
//}

//void World::handleEvent(sf::Event e, const sf::RenderWindow& window)
//{	
//	m_worldManager.handleEvent(e, window);
//	m_playingMenu.handleEvent(e, window);
//}

/*void World::update(const sf::RenderWindow& window)
{
	m_worldManager.update(window);

	bnrNumLives.setText("Lives Remaining: " + std::to_string(getNumLives()));

	for (auto& b : m_playingMenu.getWidgets())
	{
		b->update(window);
	}
}*/

//void World::render(sf::RenderTarget& renderer)
//{
	//m_worldManager.render(renderer);
	//m_playingMenu.render(renderer);
//}

//void World::handleInput()
//{
//
//}

//int World::getNumLives()
//{
//	return m_worldManager.getNumLives();
//}

//const bool& World::bShouldPushMainMenu() const
//{
//	return m_bShouldPushMainMenu;
//}

/*void World::generateButtons(const sf::RenderWindow& window)
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
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::subtract, 1, mousePos);
			}
		});

	btnPlaceTower2.setText("+1");
	btnPlaceTower2.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::subtract, -1, mousePos);
			}
		});

	btnPlaceTower3.setText("/2");
	btnPlaceTower3.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 2, mousePos);
			}
		});

	btnPlaceTower4.setText("/3");
	btnPlaceTower4.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 3, mousePos);
			}
		});

	btnPlaceTower5.setText("/5");
	btnPlaceTower5.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 5, mousePos);
			}
		});

	btnPlaceTower6.setText("/7");
	btnPlaceTower6.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 7, mousePos);
			}
		});

	btnPlaceTower7.setText("/11");
	btnPlaceTower7.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::divide, 11, mousePos);
			}
		});

	btnPlaceTower8.setText("sqrt");
	btnPlaceTower8.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::root, 2, mousePos);
			}
		});

	btnPlaceTower9.setText("cbrt");
	btnPlaceTower9.setFunction([&]()
		{
			if (m_worldManager.getbTowerBeingPlaced()) { m_worldManager.setbTowerBeingPlaced(false); }
			else
			{
				m_worldManager.setbTowerBeingPlaced(true);
				sf::Vector2f mousePos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				m_worldManager.getDummyTower()->setBasicProperties(attackType::root, 3, mousePos);
			}
		});

	btnPrevWaveStats.setText("Previous Wave Stats");
	btnPrevWaveStats.setFunction([&]()
		{

		});

	btnRestartGame.setText("Restart Game");
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

	btnMainMenu.setText("Main Menu");
	btnMainMenu.setFunction([&]()
		{
			m_bShouldPushMainMenu = true;
		});

	btnOptions.setText("Options");
	btnOptions.setFunction([&]()
		{
			// include here toggle music, colour scheme, ...
		});

	bnrNumLives.setText("Lives Remaining: " + std::to_string(m_worldManager.getNumLives());

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
	m_playingMenu.addWidget(btnOptions);
	m_playingMenu.addWidget(bnrNumLives);

}*/



