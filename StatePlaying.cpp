#include "StatePlaying.h"
#include "StateMainMenu.h"

#include "GUI\Button.h"
#include "GUI\Textbox.h"
#include "Game.h"

#include "GameObjects\Tower.h"

#include <iostream>

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
	, m_playingMenu(sf::Vector2f((float)game.getWindow().getSize().x - 200, 100),
		sf::Vector2f(300, 50))
{
	auto btnRandPath = gui::makeButton();
	btnRandPath->setText("Make Random Path");
	btnRandPath->setFunction([&]() { m_path.createRandomPath(4); });

	auto btnOrthoPath = gui::makeButton();
	btnOrthoPath->setText("Make Ortho Path");
	btnOrthoPath->setFunction([&]() { m_path.createOrthoPath(4); });

	auto btnClearPath = gui::makeButton();
	btnClearPath->setText("Clear Path");
	btnClearPath->setFunction([&]() { m_path.clear(); });

	auto btnStartLevel = gui::makeButton();
	btnStartLevel->setText("Start Level");
	btnStartLevel->setFunction([&]()
	{
		if (m_path.getVertices().size() == 0) { m_path.createRandomPath(4); }
		//clearGameObjects();
		
		m_gameObjects.push_back(new Enemy(m_path.getVertices(), 100));

	});

	auto btnMainMenu = gui::makeButton();
	btnMainMenu->setText("Main Menu");
	btnMainMenu->setFunction([&]()
	{
		clearGameObjects();
		game.pushState<StateMainMenu>(game);
	});

	m_playingMenu.addWidget(std::move(btnRandPath));
	m_playingMenu.addWidget(std::move(btnOrthoPath));
	m_playingMenu.addWidget(std::move(btnClearPath));
	m_playingMenu.addWidget(std::move(btnStartLevel));
	m_playingMenu.addWidget(std::move(btnMainMenu));

	
}

/*
void StatePlaying::addGameObject(std::unique_ptr<GameObject> object)
{
	m_gameObjects.push_back(std::move(object));
}*/

void StatePlaying::clearGameObjects()
{
	for (unsigned i = 0; i < m_gameObjects.size(); i++)
	{
		delete m_gameObjects.at(i);
	}
}

void StatePlaying::handleEvent(sf::Event e)
{
	m_playingMenu.handleEvent(e, m_pGame->getWindow());
	
}

void StatePlaying::handleInput()
{
	
}

void StatePlaying::update(sf::Time deltaTime)
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects.at(i)->update();
	}

}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(sf::RenderTarget& renderer)
{
	m_playingMenu.render(renderer);
	m_path.render(renderer);

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		//auto& item = m_gameObjects.at(i);
		//item->render(renderer);
		m_gameObjects.at(i)->render(renderer);
	}

	//renderer.draw(m_banner);
}