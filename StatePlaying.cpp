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

	auto btnClearLevel = gui::makeButton();
	btnClearLevel->setText("Clear Level");
	btnClearLevel->setFunction([&]()
	{
		m_path.clear();
		m_gameObjects.clear();
	});

	auto btnStartLevel = gui::makeButton();
	btnStartLevel->setText("Start Level");
	btnStartLevel->setFunction([&]()
	{
		if (m_path.getVertices().size() == 0) { m_path.createRandomPath(4); }

		m_gameObjects.push_back(std::make_unique<Enemy>(m_path.getVertices(), 100)); // instantiate an enemy
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
		//m_gameObjects.push_back(std::make_unique<Tower>());
		//m_gameObjects.back().doSomething...
	});

	m_playingMenu.addWidget(std::move(btnRandPath));
	m_playingMenu.addWidget(std::move(btnOrthoPath));
	m_playingMenu.addWidget(std::move(btnClearLevel));
	m_playingMenu.addWidget(std::move(btnStartLevel));
	m_playingMenu.addWidget(std::move(btnMainMenu));
	m_playingMenu.addWidget(std::move(btnPlaceTower));
	
}

/*
void StatePlaying::addGameObject(std::unique_ptr<GameObject> object)
{
	m_gameObjects.push_back(std::move(object));
}*/


void StatePlaying::handleEvent(sf::Event e)
{
	m_playingMenu.handleEvent(e, m_pGame->getWindow());

	if (e.type == sf::Event::EventType::MouseButtonReleased) // redundant with checking event type in Tower.cpp file
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		// TODO: include a function at this level to check for interference with other game objects or the path
		// - can essentially copy the code from GameObject.cpp for the function, but perhaps this function and also somehow
		// even the path object that is located at this level could be moved to a wrapper that somehow relates to level management, 
		// which would include the path, checking for interference between objects of type "GameObject" and themselves or the path,
		// and even possibly managing the waves
		
		//// THIS IS WHERE TO KEEP WORKING WHEN YOU RETURN TO CODING. May 20, 2019
		// a GameObject is currently made up only of a position and a size, so the interferesWithPath function could easily be implemented
		// outside of GameObject.cpp. It could take three arguments: a new vector which holds one new unique_ptr of a GameObject, m_gameObjects, and m_path.
		// This way the new GameObject can be placed in the other vector to minimize confusion (or ideally included alone outside of the vector), and compared with the 2nd and 3rd arguments.

		m_gameObjects.push_back(std::make_unique<Tower>());
		m_gameObjects.back()->handleEvent(e, m_pGame->getWindow()); // is a tower in this case
		if (m_gameObjects.back()->interferesWithPath(m_path)) // must also check here if new object interferes with any existing game objects
		{
			m_gameObjects.pop_back(); //remove the new tower from the back of m_gameObjects since it interferes with the path
		}
		
		/*
		std::unique_ptr<GameObject> tempObject = m_gameObjects.back();
		
		if (m_world.interferencePathAndObj(m_path, tempObject))
		{
			m_gameObjects.pop_back();
		}*/
	}

	
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

	for (const auto& obj : m_gameObjects)
	{
		obj->render(renderer);
	}

	//renderer.draw(m_banner);
}