#pragma once

#include "StateBase.h"
#include "GUI\StackMenu.h"
#include "GameObjects\WorldManager.h"
#include "GUI\Button.h"
#include "GUI\Banner.h"

//Game state for the main part of the game

class StatePlaying : public StateBase
{
public:
	StatePlaying(Game& game);

	void handleEvent	(sf::Event e)	override;
	void handleInput	()				override;
	void update			(const sf::RenderWindow& window)	override;
	//void fixedUpdate	(sf::Time deltaTime) override;
	void render			(sf::RenderTarget& renderer) override;

private:
	WorldManager m_worldManager;
	gui::StackMenu m_playingMenu;
	gui::StackMenu m_towersMenu;

	bool m_bShouldPushMainMenu = false;

	void generateButtons(Game& game) override;
	void m_populatePlayingMenu();
	void m_populateTowersMenu();

	gui::Button btnStartWave = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnPlaceTower1 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 3);
	gui::Button btnPlaceTower2 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 4);
	gui::Button btnPlaceTower3 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 5);
	gui::Button btnPlaceTower4 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 6);
	gui::Button btnPlaceTower5 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 7);
	gui::Button btnPlaceTower6 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 8);
	gui::Button btnPlaceTower7 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 9);
	gui::Button btnPlaceTower8 = gui::makeButton(gui::ButtonSizes::CIRC_LG_R, 10);
	gui::Button btnPlaceTower9 = gui::makeButton(gui::ButtonSizes::CIRC_LG_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPrevWaveStats = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnOptions = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnMainMenu = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnRestartGame = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	
	gui::Banner bnrNumLives = gui::makeBanner();

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSpriteLeft;
	sf::Sprite m_backgroundSpriteRight;



};


