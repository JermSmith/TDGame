#include "StatePlaying.h"
#include "StateMainMenu.h"

#include "Util\Math.h"
#include "Game.h"

#include <iostream>

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
	, m_world(game.getWindow())
	//, m_playingMenu(0)// sf::Vector2f(((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2), 0),
		//sf::Vector2f((float)sizes::PLAYINGMENU_X, 0))
{
	m_musicFilenames = { "Chan_Wai_Fat_-_05_-_Dream_instrumental" , "Lee_Rosevere_-_09_-_Compassion_keys_version" };

	//m_world.createRandomPath(0);

	m_backgroundTexture = ResourceHolder::get().textures.get("space");
	m_backgroundTexture.setRepeated(true);
	m_backgroundSpriteLeft.setTexture(m_backgroundTexture);
	m_backgroundSpriteRight.setTexture(m_backgroundTexture);

	m_backgroundSpriteLeft.setScale((float)sizes::WORLD_SIZE_Y / (float)m_backgroundTexture.getSize().y,
		(float)sizes::WORLD_SIZE_Y / (float)(m_backgroundTexture.getSize().y));
	m_backgroundSpriteRight.setScale((float)sizes::WORLD_SIZE_Y / (float)m_backgroundTexture.getSize().y,
		(float)sizes::WORLD_SIZE_Y / (float)(m_backgroundTexture.getSize().y));

	m_backgroundSpriteRight.setPosition(
		(float)sizes::WORLD_SIZE_Y / (float)m_backgroundTexture.getSize().y * (float)m_backgroundTexture.getSize().x, 0);
}

void StatePlaying::handleEvent(sf::Event e)
{
	m_world.handleEvent(e, m_pGame->getWindow());
	
}

void StatePlaying::handleInput()
{

}

void StatePlaying::update(const sf::RenderWindow& window)
{
	m_world.update(window);

	if (m_world.bShouldPushMainMenu())
	{
		m_pGame->pushState<StateMainMenu>(*m_pGame);
	}

	//bnrNumLives.setText("Lives Remaining: " + std::to_string(m_world.getNumLives()));

	//if (m_bGameOver)
	//{
		// do something to end the game
	//}
}

/*void StatePlaying::fixedUpdate(sf::Time deltaTime)
{

}*/

void StatePlaying::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_backgroundSpriteLeft);
	renderer.draw(m_backgroundSpriteRight);

	m_world.render(renderer);
}




