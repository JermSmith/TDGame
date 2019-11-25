#include "StatePlaying.h"
#include "StateMainMenu.h"

#include "Util\Random.h"
#include "Util\Math.h"
#include "GUI\Button.h"
#include "GUI\Textbox.h"
#include "Game.h"

#include <iostream>

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
	, m_playingMenu(sf::Vector2f(((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2), (float)gui::StackMenu::WIDGET_SPACER), 
		sf::Vector2f((float)sizes::PLAYINGMENU_X, (float)sizes::WORLD_SIZE_Y))
{
	m_world.createRandomPath(0);

	auto btnStartWave = gui::makeButton(gui::ButtonSize::Wide);
	btnStartWave->setText("Start Next Wave");
	btnStartWave->setFunction([&]()
	{
		m_world.requestStartWave();
	});

	auto btnPlaceTower1 = gui::makeButton(gui::ButtonSize::Circle3);
	btnPlaceTower1->setText("/11");
	btnPlaceTower1->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			m_world.setdummyTowerProperties(attackType::divide, 11);
		}
	});

	auto btnPlaceTower2 = gui::makeButton(gui::ButtonSize::Circle3);
	btnPlaceTower2->setText("-1");
	btnPlaceTower2->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			m_world.setdummyTowerProperties(attackType::subtract, 1); 
		}
	});

	auto btnPlaceTower3 = gui::makeButton(gui::ButtonSize::Circle3);
	btnPlaceTower3->setText("SQRT");
	btnPlaceTower3->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			m_world.setdummyTowerProperties(attackType::root, 2);
		}
	});

	auto btnPlaceTower4 = gui::makeButton(gui::ButtonSize::Circle3);
	btnPlaceTower4->setText("+1");
	btnPlaceTower4->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			m_world.setdummyTowerProperties(attackType::subtract, -1);
		}
	});

	auto btnPlaceTower5 = gui::makeButton(gui::ButtonSize::Circle3);
	btnPlaceTower5->setText("/5");
	btnPlaceTower5->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			m_world.setdummyTowerProperties(attackType::divide, 5);
		}
	});

	auto btnPlaceTower6 = gui::makeButton(gui::ButtonSize::Circle3);
	btnPlaceTower6->setText("/7");
	btnPlaceTower6->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			m_world.setdummyTowerProperties(attackType::divide, 7);
		}
	});

	// TODO: allow for the addition of 7th, 8th buttons etc.
	// TODO: figure out where wave stats, tower stats, shop, inventory, etc. will be displayed
	/*auto btnPlaceTower7 = gui::makeButton(gui::ButtonSize::Circle3);
	btnPlaceTower7->setText("/11");
	btnPlaceTower7->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			m_world.setdummyTowerProperties(attackType::divide, 11);
		}
	});

	auto btnPlaceTower8 = gui::makeButton(gui::ButtonSize::Circle3);
	btnPlaceTower8->setText("/13");
	btnPlaceTower8->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else
		{
			m_world.setBoolTowerBeingPlaced(true);
			m_world.setdummyTowerProperties(attackType::divide, 13);
		}
	});*/

	auto btnNewPath = gui::makeButton(gui::ButtonSize::Wide);
	btnNewPath->setText("New Path");
	btnNewPath->setFunction([&]()
	{
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

	auto btnMainMenu = gui::makeButton(gui::ButtonSize::Wide);
	btnMainMenu->setText("Main Menu");
	btnMainMenu->setFunction([&]()
	{
		game.pushState<StateMainMenu>(game);
	});

	auto btnPrevWaveStats = gui::makeButton(gui::ButtonSize::Wide);
	btnPrevWaveStats->setText("Previous Wave Stats");
	btnPrevWaveStats->setFunction([&]()
	{
		
	});








	m_playingMenu.addWidget(std::move(btnStartWave));
	m_playingMenu.addWidget(std::move(btnPlaceTower1));
	m_playingMenu.addWidget(std::move(btnPlaceTower2));
	m_playingMenu.addWidget(std::move(btnPlaceTower3));
	m_playingMenu.addWidget(std::move(btnPlaceTower4));
	m_playingMenu.addWidget(std::move(btnPlaceTower5));
	m_playingMenu.addWidget(std::move(btnPlaceTower6));
	//m_playingMenu.addWidget(std::move(btnPlaceTower7));
	//m_playingMenu.addWidget(std::move(btnPlaceTower8));
	m_playingMenu.addWidget(std::move(btnNewPath));
	m_playingMenu.addWidget(std::move(btnPrevWaveStats));
	m_playingMenu.addWidget(std::move(btnMainMenu));

	
}

void StatePlaying::handleEvent(sf::Event e)
{
	m_playingMenu.handleEvent(e, m_pGame->getWindow());
	m_world.handleEvent(e, m_pGame->getWindow());
	
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(sf::Time deltaTime)
{
	m_world.update(m_pGame->getWindow());
}

/*void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}*/

void StatePlaying::render(sf::RenderTarget& renderer)
{
	m_playingMenu.render(renderer);

	m_world.render(renderer);

	//renderer.draw(m_banner);
}

