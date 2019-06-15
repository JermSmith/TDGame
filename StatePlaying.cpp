#include "StatePlaying.h"
#include "StateMainMenu.h"

#include "GUI\Button.h"
#include "GUI\Textbox.h"
#include "Game.h"

#include "GameObjects\World.h"
//#include "GameObjects\Tower.h"

#include <iostream>

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
	, m_playingMenu(sf::Vector2f((float)game.getWindow().getSize().x - 200, 100),
		sf::Vector2f(300, 50))
{
	auto btnRandPath = gui::makeButton();
	btnRandPath->setText("Make Random Path");
	//btnRandPath->setFunction([&]() { m_path.createRandomPath(4); });

	auto btnOrthoPath = gui::makeButton();
	btnOrthoPath->setText("Make Ortho Path");
	//btnOrthoPath->setFunction([&]() { m_path.createOrthoPath(4); });

	auto btnClearLevel = gui::makeButton();
	btnClearLevel->setText("Clear Level");
	btnClearLevel->setFunction([&]()
	{
		//m_path.clear();
		//m_gameObjects.clear();
	});

	auto btnStartLevel = gui::makeButton();
	btnStartLevel->setText("Start Level");
	btnStartLevel->setFunction([&]()
	{
		//if (m_path.getVertices().size() == 0) { m_path.createRandomPath(4); }

		//m_gameObjects.push_back(std::make_unique<Enemy>(m_path.getVertices(), 100)); // instantiate an enemy
	});

	auto btnMainMenu = gui::makeButton();
	btnMainMenu->setText("Main Menu");
	btnMainMenu->setFunction([&]()
	{
		game.pushState<StateMainMenu>(game);
	});

	auto btnPlaceTower = gui::makeButton();
	btnPlaceTower->setText("Place Tower");
	btnPlaceTower->setFunction([&]()
	{
		if (m_world.getBoolTowerBeingPlaced()) { m_world.setBoolTowerBeingPlaced(false); }
		else { m_world.setBoolTowerBeingPlaced(true); }
	});

	m_playingMenu.addWidget(std::move(btnRandPath));
	m_playingMenu.addWidget(std::move(btnOrthoPath));
	m_playingMenu.addWidget(std::move(btnClearLevel));
	m_playingMenu.addWidget(std::move(btnStartLevel));
	m_playingMenu.addWidget(std::move(btnMainMenu));
	m_playingMenu.addWidget(std::move(btnPlaceTower));
	
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
	m_world.update(deltaTime, m_pGame->getWindow());
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(sf::RenderTarget& renderer)
{
	m_playingMenu.render(renderer);

	m_world.render(renderer);

	//renderer.draw(m_banner);
}