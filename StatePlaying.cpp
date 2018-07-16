#include "StatePlaying.h"
#include "StateMainMenu.h"

#include "GUI\Button.h"
#include "GUI\Textbox.h"
#include "Game.h"

#include "GameObjects\Tower.h"

#include <iostream>

std::string test;

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
	, m_playingMenu(sf::Vector2f((float)game.getWindow().getSize().x - 200, 100),
		sf::Vector2f(300, 50))
{
	auto btnRandPath = gui::makeButton();
	btnRandPath->setText("Make Random Path");
	btnRandPath->setFunction([&]()
	{
		m_path.createRandomPath(1);
		//b_ = m_tower.interferesWithPath(m_path);
		//std::cout << "interferes with path? " << std::to_string(b_) << std::endl;
	});

	auto btnOrthoPath = gui::makeButton();
	btnOrthoPath->setText("Make Ortho Path");
	btnOrthoPath->setFunction([&]()
	{
		m_path.createOrthoPath(1);
	});

	auto btnMainMenu = gui::makeButton();
	btnMainMenu->setText("Main Menu");
	btnMainMenu->setFunction([&]()
	{
		game.pushState<StateMainMenu>(game);
	});

	m_playingMenu.addWidget(std::move(btnRandPath));
	m_playingMenu.addWidget(std::move(btnOrthoPath));
	m_playingMenu.addWidget(std::move(btnMainMenu));

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
	
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}

void StatePlaying::render(sf::RenderTarget& renderer)
{
	m_playingMenu.render(renderer);
	m_path.render(renderer);
	m_tower.render(renderer);
	//renderer.draw(m_banner);
}