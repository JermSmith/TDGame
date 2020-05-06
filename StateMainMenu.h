#pragma once

#include "StateBase.h"
#include "GUI\StackMenu.h"
#include "GUI\Button.h"

//Game state for main menu

class StateMainMenu : public StateBase
{
public:
	StateMainMenu(Game& game);
	
	void handleEvent	(sf::Event e)	override;
	void handleInput	()				override;
	void update			(const sf::RenderWindow& window)	override;
	void render			(sf::RenderTarget& renderer) override;

private:
	void generateButtons(Game& game) override;

	gui::StackMenu m_mainMenu;
	gui::StackMenu m_optionsMenu;

	gui::Button btnNewGame = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnLoadGame = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnOptions = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnHowToPlay = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnHighScores = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnExit = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);

	gui::Button btnToggleMusic = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnColourScheme = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Button btnMainMenu = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);

	void m_generateOptionsButtons(Game& game);
};


