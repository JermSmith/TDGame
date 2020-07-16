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
	bool m_bShouldPushMainMenu = false;
	
	WorldManager m_worldManager;

	gui::StackMenu m_playingMenu;
	gui::StackMenu m_towersMenu;

	gui::StackMenu m_optionsMenu;
	gui::StackMenu m_confirmExitMenu;
	gui::StackMenu m_confirmResetGameMenu;
	gui::StackMenu m_prevWaveStatsMenu;

	void generateWidgets(Game& game) override;
	void m_populatePlayingMenu();
	void m_populateTowersMenu();
	void m_populateOptionsMenu();
	void m_populateConfirmExitMenu();
	void m_populateConfirmResetGameMenu();
	void m_populatePrevWaveStatsMenu();

	// PLAYING MENU BUTTONS

	gui::Button btnStartWave = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnPrevWaveStats = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnOptions = gui::makeButton(gui::ButtonSizes::RECT_SM);
	gui::Button btnMainMenu = gui::makeButton(gui::ButtonSizes::RECT_SM);
	gui::Button btnSaveGame = gui::makeButton(gui::ButtonSizes::RECT_SM);
	gui::Button btnRestartGame = gui::makeButton(gui::ButtonSizes::RECT_SM);

	// TOWERS BUTTONS

	gui::Button btnPlaceTower1 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 3);
	gui::Button btnPlaceTower2 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 4);
	gui::Button btnPlaceTower3 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 5);
	gui::Button btnPlaceTower4 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 6);
	gui::Button btnPlaceTower5 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 7);
	gui::Button btnPlaceTower6 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 8);
	gui::Button btnPlaceTower7 = gui::makeButton(gui::ButtonSizes::CIRC_SM_R, 9);
	gui::Button btnPlaceTower8 = gui::makeButton(gui::ButtonSizes::CIRC_LG_R, 10);
	gui::Button btnPlaceTower9 = gui::makeButton(gui::ButtonSizes::CIRC_LG_R, gui::ButtonSizes::CIRC_NUMPTS);
	
	gui::Banner bnrNumLives = gui::makeBanner((float)sizes::PLAYINGMENU_X, gui::ButtonSizes::RECT_BANNER_H);

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSpriteLeft;
	sf::Sprite m_backgroundSpriteRight;

	// OPTIONS MENU BUTTONS

	gui::Button btnToggleMusic = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnToggleColourScheme = gui::makeButton(gui::ButtonSizes::RECT_LG);

	// EXIT TO MENU CONFIRM BUTTONS

	gui::Banner bnrExitPrompt = gui::makeBanner(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_BANNER_H);
	gui::Button btnYesExit = gui::makeButton(gui::ButtonSizes::RECT_SM);
	gui::Button btnNoDontExit = gui::makeButton(gui::ButtonSizes::RECT_SM);

	// RESET GAME CONFIRM BUTTONS

	gui::Banner bnrResetPrompt = gui::makeBanner(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_BANNER_H);
	gui::Button btnYesReset = gui::makeButton(gui::ButtonSizes::RECT_SM);
	gui::Button btnNoDontReset = gui::makeButton(gui::ButtonSizes::RECT_SM);

	// PREV WAVE STATS

	gui::Banner bnrPrevWaveStat1 = gui::makeBanner(gui::ButtonSizes::RECT_LG);
	gui::Banner bnrPrevWaveStat2 = gui::makeBanner(gui::ButtonSizes::RECT_LG);
	gui::Banner bnrPrevWaveStat3 = gui::makeBanner(gui::ButtonSizes::RECT_LG);


};




