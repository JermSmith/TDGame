#pragma once

#include "StateBase.h"
#include "GUI\StackMenu.h"
#include "GameObjects\Path.h"
#include "GameObjects\Tower.h"
#include "GameObjects\Enemy.h"

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

	//void addGameObject(std::unique_ptr<GameObject> object);

	void clearGameObjects();
	std::vector<GameObject*> m_gameObjects;

};