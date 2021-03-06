#pragma once

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>

#include "States\StateBase.h"
#include "Util\NonMovable.h"
#include "Util\FPSCounter.h"

/*
	Main controlling class of the game.
	Handles state switches and the main loop, as well as counting FPS
*/

class Game: public NonCopyable, public NonMovable
{
public:
	Game();

	void run();

	template<typename T, typename... Args> void pushState(Args&&... args);
	void pushState(std::unique_ptr<StateBase> state);
	//void popState();
	void exitGame();
	//template <typename T, typename... Args> void changeState(Args&&... args);

	const sf::RenderWindow& getWindow() const;

	bool getMusicRequestStatus() { return m_bMusicRequestStatus; } // new
	void setMusicRequestStatus(bool tf) { m_bMusicRequestStatus = tf; } // new

private:
	void handleEvent();
	void tryPop();

	StateBase& getCurrentState();

	sf::RenderWindow m_window;
	std::vector<std::unique_ptr<StateBase>> m_states;

	FPSCounter counter;

	bool m_shouldPop = false;
	bool m_shouldExit = false;
	//bool m_shouldChangeState = false;
	std::unique_ptr<StateBase> m_change;

	bool m_bMusicRequestStatus = true;
	bool m_bRandomizeMusic = true;
};

template<typename T, typename... Args> inline void Game::pushState(Args&&... args)
{
	pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

/*
template<typename T, typename... Args> inline void Game::changeState(Args&&... args)
{
	m_change = std::make_unique<T>(std::forward<Args>(args)...);
	m_shouldPop = true;
	m_shouldChangeState = true;
}*/

