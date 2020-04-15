#pragma once

#include <SFML\Graphics.hpp>
#include "Random.h"
#include <iostream>

namespace colours
{
	sf::Color towerTextColour = sf::Color::Black;
	sf::Color towerFillColour = sf::Color::Cyan;
	sf::Color towerRangeFillColour = sf::Color(255, 255, 255, 63);

	sf::Color defaultButtonFillColour = sf::Color::Black;
	sf::Color buttonHoverColour = sf::Color(155, 155, 155);

	sf::Color selectRandomColor()
	{
		std::vector<sf::Color> coloursVector = {
		sf::Color(0, 51, 102), sf::Color(0, 51, 153), sf::Color(0, 51, 204), sf::Color(0, 51, 255),
		sf::Color(0, 102, 0), sf::Color(0, 102, 51), sf::Color(0, 102, 102), sf::Color(0, 102, 153), sf::Color(0, 102, 204), sf::Color(0, 102, 255),
		sf::Color(0, 153, 0), sf::Color(0, 153, 51), sf::Color(0, 153, 102), sf::Color(0, 153, 153), sf::Color(0, 153, 204), sf::Color(0, 153, 155),
		sf::Color(0, 204, 0), sf::Color(0, 204, 51), sf::Color(0, 204, 102), sf::Color(0, 204, 153), sf::Color(0, 204, 204), sf::Color(0, 204, 255),
		sf::Color(0, 255, 0), sf::Color(0, 255, 51), sf::Color(0, 255, 102), sf::Color(0, 255, 153), sf::Color(0, 255, 204), sf::Color(0, 255, 255),
		sf::Color(51, 0, 102), sf::Color(51, 0, 153), sf::Color(51, 0, 204), sf::Color(51, 0, 255),
		sf::Color(51, 51, 102), sf::Color(51, 51, 153), sf::Color(51, 51, 204), sf::Color(51, 51, 255),
		sf::Color(51, 102, 0), sf::Color(51, 102, 51), sf::Color(51, 102, 102), sf::Color(51, 102, 153), sf::Color(51, 102, 204), sf::Color(51, 102, 255),
		sf::Color(51, 153, 0), sf::Color(51, 153, 51), sf::Color(51, 153, 102), sf::Color(51, 153, 153), sf::Color(51, 153, 204), sf::Color(51, 153, 255),
		sf::Color(51, 204, 0), sf::Color(51, 204, 51), sf::Color(51, 204, 102), sf::Color(51, 204, 153), sf::Color(51, 204, 204), sf::Color(51, 204, 255),
		sf::Color(51, 255, 0), sf::Color(51, 255, 51), sf::Color(51, 255, 102), sf::Color(51, 255, 153), sf::Color(51, 255, 204), sf::Color(51, 255, 255),
		sf::Color(102, 0, 0), sf::Color(102, 0, 51), sf::Color(102, 0, 102), sf::Color(102, 0, 153), sf::Color(102, 0, 204), sf::Color(102, 0, 255),
		sf::Color(102, 51, 0), sf::Color(102, 51, 51), sf::Color(102, 51, 102), sf::Color(102, 51, 153), sf::Color(102, 51, 204), sf::Color(102, 51, 255),
		sf::Color(102, 102, 0), sf::Color(102, 102, 51), sf::Color(102, 102, 102), sf::Color(102, 102, 153), sf::Color(102, 102, 204), sf::Color(102, 102, 255),
		sf::Color(102, 153, 0), sf::Color(102, 153, 51), sf::Color(102, 153, 102), sf::Color(102, 153, 153), sf::Color(102, 153, 204), sf::Color(102, 153, 255),
		sf::Color(102, 204, 0), sf::Color(102, 204, 51), sf::Color(102, 204, 102), sf::Color(102, 204, 153), sf::Color(102, 204, 204), sf::Color(102, 204, 255),
		sf::Color(102, 255, 0), sf::Color(102, 255, 51), sf::Color(102, 255, 102), sf::Color(102, 255, 153), sf::Color(102, 255, 204), sf::Color(102, 255, 255),
		sf::Color(153, 0, 0), sf::Color(153, 0, 51), sf::Color(153, 0, 102), sf::Color(153, 0, 153), sf::Color(153, 0, 204), sf::Color(153, 0, 255),
		sf::Color(153, 51, 0), sf::Color(153, 51, 51), sf::Color(153, 51, 102), sf::Color(153, 51, 153), sf::Color(153, 51, 204), sf::Color(153, 51, 255),
		sf::Color(153, 102, 0), sf::Color(153, 102, 51), sf::Color(153, 102, 102), sf::Color(153, 102, 153), sf::Color(153, 102, 204), sf::Color(153, 102, 255),
		sf::Color(153, 153, 0), sf::Color(153, 153, 51), sf::Color(153, 153, 102), sf::Color(153, 153, 153), sf::Color(153, 153, 204), sf::Color(153, 153, 255),
		sf::Color(153, 204, 0), sf::Color(153, 204, 51), sf::Color(153, 204, 102), sf::Color(153, 204, 153), sf::Color(153, 204, 204), sf::Color(153, 204, 255),
		sf::Color(153, 255, 0), sf::Color(153, 255, 51), sf::Color(153, 255, 102), sf::Color(153, 255, 153), sf::Color(153, 255, 204), sf::Color(153, 255, 255),
		sf::Color(204, 0, 0), sf::Color(204, 0, 51), sf::Color(204, 0, 102), sf::Color(204, 0, 153), sf::Color(204, 0, 204), sf::Color(204, 0, 255),
		sf::Color(204, 51, 0), sf::Color(204, 51, 51), sf::Color(204, 51, 102), sf::Color(204, 51, 153), sf::Color(204, 51, 204), sf::Color(204, 51, 255),
		sf::Color(204, 102, 0), sf::Color(204, 102, 51), sf::Color(204, 102, 102), sf::Color(204, 102, 153), sf::Color(204, 102, 204), sf::Color(204, 102, 255),
		sf::Color(204, 153, 0), sf::Color(204, 153, 51), sf::Color(204, 153, 102), sf::Color(204, 153, 153), sf::Color(204, 153, 204), sf::Color(204, 153, 255),
		sf::Color(204, 204, 0), sf::Color(204, 204, 51), sf::Color(204, 204, 102), sf::Color(204, 204, 153), sf::Color(204, 204, 204), sf::Color(204, 204, 255),
		sf::Color(204, 255, 0), sf::Color(204, 255, 51), sf::Color(204, 255, 102), sf::Color(204, 255, 153), sf::Color(204, 255, 204), sf::Color(204, 255, 255),
		sf::Color(255, 0, 0), sf::Color(255, 0, 51), sf::Color(255, 0, 102), sf::Color(255, 0, 153), sf::Color(255, 0, 204), sf::Color(255, 0, 255),
		sf::Color(255, 51, 0), sf::Color(255, 51, 51), sf::Color(255, 51, 102), sf::Color(255, 51, 153), sf::Color(255, 51, 204), sf::Color(255, 51, 255),
		sf::Color(255, 102, 0), sf::Color(255, 102, 51), sf::Color(255, 102, 102), sf::Color(255, 102, 153), sf::Color(255, 102, 204), sf::Color(255, 102, 255),
		sf::Color(255, 153, 0), sf::Color(255, 153, 51), sf::Color(255, 153, 102), sf::Color(255, 153, 153), sf::Color(255, 153, 204), sf::Color(255, 153, 255),
		sf::Color(255, 204, 0), sf::Color(255, 204, 51), sf::Color(255, 204, 102), sf::Color(255, 204, 153), sf::Color(255, 204, 204), sf::Color(255, 204, 255),
		sf::Color(255, 255, 0), sf::Color(255, 255, 51), sf::Color(255, 255, 102), sf::Color(255, 255, 153), sf::Color(255, 255, 204)
		};

		static Random<> rand;
		int index = rand.getIntInRange(0, coloursVector.size() - 1);
		return coloursVector.at(index);
	}
};


