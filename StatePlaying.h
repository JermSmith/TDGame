#pragma once

#include "StateBase.h"
#include "GUI\StackMenu.h"
#include "GameObjects\World.h"
#include "GUI\Button.h"
#include "GUI\Banner.h"

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

	gui::RectangularButton btnStartWave = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::CircularButton btnPlaceTower1 = gui::makeCircularButton(gui::ButtonSize::Circle3);
	gui::CircularButton btnPlaceTower2 = gui::makeCircularButton(gui::ButtonSize::Circle3);
	gui::CircularButton btnPlaceTower3 = gui::makeCircularButton(gui::ButtonSize::Circle3);
	gui::CircularButton btnPlaceTower4 = gui::makeCircularButton(gui::ButtonSize::Circle3);
	gui::CircularButton btnPlaceTower5 = gui::makeCircularButton(gui::ButtonSize::Circle3);
	gui::CircularButton btnPlaceTower6 = gui::makeCircularButton(gui::ButtonSize::Circle3);
	gui::CircularButton btnPlaceTower7 = gui::makeCircularButton(gui::ButtonSize::Circle3);
	gui::CircularButton btnPlaceTower8 = gui::makeCircularButton(gui::ButtonSize::Circle2);
	gui::CircularButton btnPlaceTower9 = gui::makeCircularButton(gui::ButtonSize::Circle2);
	gui::RectangularButton btnPrevWaveStats = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnRestartGame = gui::makeRectangularButton(gui::ButtonSize::Wide);
	gui::RectangularButton btnMainMenu = gui::makeRectangularButton(gui::ButtonSize::Small);
	gui::RectangularButton btnToggleMusic = gui::makeRectangularButton(gui::ButtonSize::Small);
	gui::Banner bnrNumLives = gui::makeBanner();

};


