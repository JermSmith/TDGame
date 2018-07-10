#pragma once

#include "StateBase.h"
#include "GUI\StackMenu.h"
#include "GameObjects\Path.h"
#include "GameObjects\Tower.h"

//Game state for the main part of the game

class StatePlaying : public StateBase
{
public:
	StatePlaying(Game& game);

	void handleEvent	(sf::Event e)	override;
	void handleInput	()				override;
	void update			(sf::Time deltaTime) override;
	void fixedUpdate	(sf::Time deltaTime) override;
	void render			(sf::RenderTarget& renderer) override;

private:
	gui::StackMenu m_playingMenu;
	sf::RectangleShape m_banner;
	Path m_path;
	Tower m_tower;

};