#include "Game.h"
#include "States\StateMainMenu.h"
#include "Util\Math.h"
#include <iostream>

Game::Game() : m_window({ sizes::WORLD_SIZE_X, sizes::WORLD_SIZE_Y }, "Prime TD")
{
	m_window.setPosition({ 0, 0 });// { m_window.getPosition().x, 0 });
	m_window.setFramerateLimit(60);
	pushState<StateMainMenu>(*this);
}

//Runs the main loop
void Game::run()
{
	// Fixed Time Update stuff
	/*
	constexpr unsigned TPS = 30; //ticks per second
	const sf::Time timePerUpdate = sf::seconds(1.0f / float(TPS));
	unsigned ticks = 0;
	*/

	sf::Clock timer;
	auto lastTime = sf::Time::Zero;
	//auto lag = sf::Time::Zero; // used for Fixed Time Update

	//Main loop of the game
	while (m_window.isOpen() && !m_states.empty())
	{
		auto& state = getCurrentState();

		//Get times
		auto time = timer.getElapsedTime();
		auto elapsed = time - lastTime;
		lastTime = time;
		//lag += elapsed; // used for Fixed Time Update

		//Real time update
		state.handleInput();
		state.update(m_window);

		state.playMusic(m_bRandomizeMusic);// , m_bMusicRequestStatus);
		//if (m_bMusicRequestStatus) { state.unmuteMusic(); }
		//else if (!m_bMusicRequestStatus) { state.muteMusic(); }

		counter.update();

		
		//Fixed time update
		/*
		while (lag >= timePerUpdate)
		{
			ticks++;
			lag -= timePerUpdate;
			state.fixedUpdate(elapsed);
		}
		*/

		//Render
		m_window.clear();
		state.render(m_window);
		counter.draw(m_window);
		m_window.display();

		//Handle window events
		handleEvent();
		tryPop();
	}
}

//Tries to pop the current game state
void Game::tryPop()
{
	if (m_shouldPop)
	{
		m_shouldPop = false;
		if (m_shouldExit)
		{
			m_states.clear();
			return;
		}
		//else if (m_shouldChangeState)
		//{
		//	m_shouldChangeState = false;
		//	m_states.pop_back();
		//	pushState(std::move(m_change));
		//	return;
		//}

		m_states.pop_back();
	}
}

//Handles window events, called every frame
void Game::handleEvent()
{
	sf::Event e;

	while (m_window.pollEvent(e))
	{
		std::pair<unsigned int, unsigned int> prevWindowSize = std::make_pair(sizes::WORLD_SIZE_X, sizes::WORLD_SIZE_Y);
		
		getCurrentState().handleEvent(e);
		switch (e.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button == sf::Mouse::Right)
			{
				m_window.setSize(sf::Vector2u(sizes::WORLD_SIZE_X, sizes::WORLD_SIZE_Y));
				m_window.setView(m_window.getDefaultView());
				m_window.setPosition({ 0, 0 });
			}
			break;
		
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::F11)
			{
				m_window.create(sf::VideoMode(), "Prime TD", sf::Style::Fullscreen);
				m_window.setFramerateLimit(60);
			}
			else if (e.key.code == sf::Keyboard::Escape)
			{
				m_window.create(sf::VideoMode(sizes::WORLD_SIZE_X, sizes::WORLD_SIZE_Y), "Prime TD", sf::Style::Default);
				m_window.setFramerateLimit(60);
				m_window.setPosition({ 0, 0 });
			}
			break;

		case sf::Event::Resized:
			if ((float)m_window.getSize().x / (float)m_window.getSize().y <
				((float)sizes::WORLD_SIZE_X / (float)sizes::WORLD_SIZE_Y)) //AR is "tall", horiz dimension fits in window
			{
				sf::View resizedView = sf::View(sf::FloatRect(0, 0, (float)sizes::WORLD_SIZE_X, (float)sizes::WORLD_SIZE_Y));

				resizedView.setViewport(sf::FloatRect(0.f, 0.f, 1.0f,
					(float)sizes::WORLD_SIZE_Y * ((float)m_window.getSize().x / (float)sizes::WORLD_SIZE_X) / (float)m_window.getSize().y));

				m_window.setView(resizedView);
			}
			
			else if ((float)m_window.getSize().x / (float)m_window.getSize().y >
				((float)sizes::WORLD_SIZE_X / (float)sizes::WORLD_SIZE_Y)) //AR is "wide", vertical dimension fits in window
			{
				sf::View resizedView = sf::View(sf::FloatRect(0, 0, (float)sizes::WORLD_SIZE_X, (float)sizes::WORLD_SIZE_Y));

				resizedView.setViewport(sf::FloatRect(0.f, 0.f,
					(float)sizes::WORLD_SIZE_X * ((float)m_window.getSize().y / (float)sizes::WORLD_SIZE_Y) / (float)m_window.getSize().x,
					1.0f));

				m_window.setView(resizedView);
			}

			prevWindowSize = std::make_pair(m_window.getSize().x, m_window.getSize().y);

			break;

		default:
			break;

		}
	}
}

//Returns a reference to the current game state
StateBase& Game::getCurrentState()
{
	return *m_states.back();
}

void Game::pushState(std::unique_ptr<StateBase> state)
{
	if (m_states.size() > 0)
	{
		m_states.back()->stopMusic();
	}
	m_states.push_back(std::move(state));
}

//Flags a boolean for the game to pop state
//void Game::popState()
//{
//	m_shouldPop = true;
//}

void Game::exitGame()
{
	m_shouldPop = true;
	m_shouldExit = true;
}

const sf::RenderWindow& Game::getWindow() const
{
	return m_window;
}

