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
	void update			()				override;
	void render			(sf::RenderTarget& renderer) override;
	void generateButtons(Game& game) override;

private:
	gui::StackMenu m_mainMenu;
	gui::StackMenu m_optionsMenu;

	gui::RectangularButton btnNewGame = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnLoadGame = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnOptions = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnHowToPlay = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnHighScores = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnExit = gui::makeRectangularButton(gui::ButtonSize::Wide);

	gui::RectangularButton btnToggleMusic = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnColourScheme = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnMainMenu = gui::makeRectangularButton(gui::ButtonSize::Wide);

	void m_generateOptionsButtons(Game& game);
};

