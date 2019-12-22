#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Util/NonCopyable.h"

class Game;

class StateBase : public NonCopyable
{
public:
	StateBase(Game& game) : m_pGame(&game) {}

	virtual ~StateBase() = default;

	virtual void handleEvent(sf::Event e) {}
	virtual void handleInput() = 0;
	virtual void update(sf::Time deltaTime) {}
	//virtual void fixedUpdate(sf::Time deltaTime) {}
	virtual void render(sf::RenderTarget& renderer) = 0;

	void playMusic()
	{
		if (musicIterator == m_musicFilenames.size())
		{
			musicIterator = 0; //reset to the beginning
		}

		if (m_music.getStatus() != sf::Music::Status::Playing)
		{
			m_music.openFromFile("res/audio_wav/" + m_musicFilenames.at(musicIterator) + ".wav");
			m_music.play();
			musicIterator++;
		}
	}

	void stopMusic()
	{
		m_music.stop();
	}

protected:
	Game* m_pGame;
	sf::Music m_music;
	std::vector<std::string> m_musicFilenames;
	
private:
	int musicIterator = 0;

};

