#include "StatePlaying.h"
#include "StateMainMenu.h"

#include "GUI\Button.h"
#include "GUI\Textbox.h"
#include "Game.h"

#include <iostream>

std::string test;

StatePlaying::StatePlaying(Game& game) : StateBase(game), m_playingMenu(game.getWindow(), 50)
{
	auto btn1 = std::make_unique<gui::Button>();
	btn1->setText("Button 1");
	btn1->setFunction([&]()
	{
		std::cout << "Button 1 clicked!" << '\n';
	});
	m_playingMenu.addWidget(std::move(btn1));

	auto btn2 = gui::makeButton();
	btn2->setText("Main Menu");
	btn2->setFunction([&]()
	{
		std::cout << "Main Menu Button clicked!" << std::endl;
		game.pushState<StateMainMenu>(game);
	});
	m_playingMenu.addWidget(std::move(btn2));
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
	//renderer.draw(m_banner);
}