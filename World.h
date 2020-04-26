#pragma once

#include "Tower.h"
#include "Enemy.h"
#include "WaveManager.h"
#include "TowerManager.h"
#include "Cursor.h"

#include "GUI\StackMenu.h"
#include "GUI\Button.h"
#include "GUI\Banner.h"

#include <memory>

class World
{
public:

	World(const sf::RenderWindow& window);
	
	void handleEvent(sf::Event e, const sf::RenderWindow& window);
	void handleInput();
	void update(const sf::RenderWindow& window);
	void render(sf::RenderTarget& renderer);

	//void fixedUpdate(sf::Time deltaTime);

	void createOrthoPath(int numInternalVertices);
	void createRandomPath(int numInternalVertices);
	void clearScene();

	const bool& bShouldPushMainMenu() const;

private:
	Path m_path;
	WaveManager m_waveManager;
	TowerManager m_towerManager;
	gui::StackMenu m_playingMenu;

	bool m_bShouldPushMainMenu = false;
	
	//int m_numLives;
	int getNumLives();

	void requestStartWave();
	
	void generateButtons(const sf::RenderWindow& window);

	gui::Button btnStartWave = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnPlaceTower1 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPlaceTower2 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPlaceTower3 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPlaceTower4 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPlaceTower5 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPlaceTower6 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPlaceTower7 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPlaceTower8 = gui::makeButton(gui::ButtonSizes::CIRC_LG_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPlaceTower9 = gui::makeButton(gui::ButtonSizes::CIRC_LG_R, gui::ButtonSizes::CIRC_NUMPTS);
	gui::Button btnPrevWaveStats = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnRestartGame = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnMainMenu = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnOptions = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	
	gui::Banner bnrNumLives = gui::makeBanner();

	

};

