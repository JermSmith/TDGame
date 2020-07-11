#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Util/NonCopyable.h"
#include "Util\Random.h"

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

	void playMusic(bool bRandomize)//, bool bMusicRequestStatus)
	{
		if (m_musicFilenames.size() > 0)
		{
			if (m_music.getStatus() != sf::Music::Status::Playing)
			{
				if (bRandomize) // play music from m_musicFilenames in random order
				{
					static Random<> rand;
					int musicIterator = rand.getIntInRange(0, m_musicFilenames.size() - 1);
					m_music.openFromFile("res/audio_wav/" + m_musicFilenames.at(musicIterator) + ".wav");
					m_music.play();
				}

				else // play music in order it appears in m_musicFilenames
				{
					m_music.openFromFile("res/audio_wav/" + m_musicFilenames.at(musicIterator) + ".wav");
					m_music.play();
					musicIterator++;

					if (musicIterator == m_musicFilenames.size())
					{
						musicIterator = 0; // reset to the beginning
					}
				}
			}
		}
		//if (bMusicRequestStatus) { m_music.setVolume(100); }
		//else { m_music.setVolume(0); }
	}

	void stopMusic() { m_music.stop(); }
	void muteMusic() { m_music.setVolume(0); }
	void unmuteMusic() { m_music.setVolume(100); }

protected:
	Game* m_pGame;
	std::vector<std::string> m_musicFilenames;
	
private:
	virtual void generateWidgets(Game& game) = 0;

	sf::Music m_music;
	int musicIterator = 0;
	//bool m_bMusicRequested = true;

};

