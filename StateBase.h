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
	virtual void update(const sf::RenderWindow& window) {}
	//virtual void fixedUpdate(sf::Time deltaTime) {}
	virtual void render(sf::RenderTarget& renderer) = 0;

	void playMusic(bool bMusicRequestStatus)
	{
		if (m_musicFilenames.size() > 0)
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

		if (bMusicRequestStatus) { m_music.setVolume(100); }
		else { m_music.setVolume(0); }
	}

	void stopMusic() { m_music.stop(); }
	void muteMusic() { m_music.setVolume(0); }
	void unmuteMusic() { m_music.setVolume(100); }

protected:
	Game* m_pGame;
	std::vector<std::string> m_musicFilenames;
	
private:
	virtual void generateButtons(Game& game) = 0;

	sf::Music m_music;
	int musicIterator = 0;
	//bool m_bMusicRequested = true;

};

