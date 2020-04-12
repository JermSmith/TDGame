#pragma once

#include "StateBase.h"
#include "GUI\StackMenu.h"
#include "GameObjects\World.h"

//Game state for the main part of the game

class StatePlaying : public StateBase
{
public:
	StatePlaying(Game& game);

	void handleEvent	(sf::Event e)	override;
	void handleInput	()				override;
	void update			()				override;
	//void fixedUpdate	(sf::Time deltaTime) override;
	void render			(sf::RenderTarget& renderer) override;
	void generateButtons(Game& game) override;

private:
	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSpriteLeft;
	sf::Sprite m_backgroundSpriteRight;

	gui::StackMenu m_playingMenu;

	World m_world;

	bool m_bGameOver = false;

};

