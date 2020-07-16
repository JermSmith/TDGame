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
	gui::StackMenu m_mainMenu;
	gui::StackMenu m_optionsMenu;
	
	void generateWidgets(Game& game) override;
	void m_populateMainMenu();
	void m_populateOptionsMenu();

	gui::Button btnNewGame = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnLoadGame = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnOptions = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnHowToPlay = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnHighScores = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnExit = gui::makeButton(gui::ButtonSizes::RECT_LG);

	gui::Button btnToggleMusic = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnColourScheme = gui::makeButton(gui::ButtonSizes::RECT_LG);
	gui::Button btnMainMenu = gui::makeButton(gui::ButtonSizes::RECT_LG);

};


