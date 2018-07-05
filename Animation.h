#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
	struct Frame
	{
		Frame(const sf::IntRect& bnds, sf::Time dly) : bounds(bnds), delay(dly) { }

		sf::IntRect bounds; // the area in a texture of the frame
		sf::Time delay; // time to delay to next frame
	};

	Animation(unsigned frameWidth, unsigned frameHeight);

	void addFrame(unsigned index, sf::Time delay);

	const sf::IntRect& getFrame();

private:
	sf::Clock m_timer;				// timer for progressing the animation

	std::vector<Frame> m_frames;	// list of animation frames

	unsigned m_framePointer = 0;	// index of the currect active frame
	const unsigned FRAME_WIDTH;
	const unsigned FRAME_HEIGHT;

};