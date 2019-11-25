#include "TowerManager.h"
#include <iostream>

// TODO: find somewhere in the code (probably create a new class or two) to manage the store, inventory and world.
// store is the available towers; inventory is towers that have been purchased/accumulated; world is what has been placed along the path.
// towers go from store --> inventory --> world

TowerManager::TowerManager()
{

}

void TowerManager::update(const sf::RenderWindow& window, const Path& path, std::vector<std::unique_ptr<Enemy>>* enemies)
{
	m_dummyTower.update(window, path, m_divRootTowers, m_subAddTowers, m_bTowerBeingPlaced);

	// in this for loop setup, div and root towers update after each sub or add operation
	if (m_subAddTowers.size() == 0)
	{
		for (auto& divRootTower : m_divRootTowers)
		{
			divRootTower->update(enemies);
		}
	}
	else
	{
		for (auto& subAddTower : m_subAddTowers)
		{
			subAddTower->update(enemies);

			for (auto& divRootTower : m_divRootTowers)
			{
				divRootTower->update(enemies);
			}
		}
	}
}

void TowerManager::handleEvent(sf::Event e, const sf::RenderWindow& window, const Path& path)
{
	if (e.type == sf::Event::EventType::MouseButtonReleased)
	{
		m_handleEvent_TowerSelection(window);

		if (m_bTowerBeingPlaced)
		{
			// place dummy tower at mouse position to check for interference
			m_dummyTower.setPosition(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

			if (!m_dummyTower.bInterferesWithScene(m_divRootTowers, m_subAddTowers, path, window))
			{
				//no interference found with new tower and path, so can place tower
				
				m_handleEvent_InsertDummyTowerIntoVectorOfTowers(window);
				// Note that strongest towers are placed closer to front of vector, so they are updated first: 
				// -2 > -1 > +1 > +2 ; root4 > sqrt > /13 > /2

				m_bTowerBeingPlaced = false;

				std::cout << "tower strengths in subtract vector are: " << std::endl;
				for (auto& tower : m_subAddTowers)
				{
					std::cout << tower->getStrength() << std::endl;
				}
				std::cout << "tower strengths in divide vector are: " << std::endl;
				for (auto& tower : m_divRootTowers)
				{
					std::cout << tower->getStrength() << std::endl;
				}
			}
		}
	}
}

void TowerManager::render(sf::RenderTarget& renderer)
{
	for (const auto& obj : m_divRootTowers)
	{
		obj->render(renderer);
	}
	for (const auto& obj : m_subAddTowers)
	{
		obj->render(renderer);
	}

	m_dummyTower.render(renderer);
}

std::vector<std::unique_ptr<Tower>>* TowerManager::getDivRootTowers() { return &m_divRootTowers; }
std::vector<std::unique_ptr<Tower>>* TowerManager::getSubAddTowers() { return &m_subAddTowers; }

Cursor* TowerManager::getDummyTower() { return &m_dummyTower; }

const bool& TowerManager::getbTowerBeingPlaced() const
{
	return m_bTowerBeingPlaced;
}

void TowerManager::setbTowerBeingPlaced(bool tf)
{
	m_bTowerBeingPlaced = tf;
}

void TowerManager::m_handleEvent_TowerSelection(const sf::RenderWindow& window)
{
	m_bTowerWasJustSelected = false;

	m_handleEvent_TowerSelection_LoopTowers(window, &m_divRootTowers);
	if (m_bTowerWasJustSelected) // deselect all towers in subAddTowers
	{
		for (auto& subAddTower : m_subAddTowers)
		{
			subAddTower->setbIsClickedOn(false);
		}
		return; // exit the function; all towers have been deselected except the one in divRootTowers
	}
	
	m_handleEvent_TowerSelection_LoopTowers(window, &m_subAddTowers);
	if (m_bTowerWasJustSelected) // deselect all towers in divRootTowers
	{
		for (auto& divRootTower : m_divRootTowers)
		{
			divRootTower->setbIsClickedOn(false);
		}
		return; // exit the function; all towers have been deselected except the one in subAddTowers
	}

	if (!m_bTowerWasJustSelected)
	{
		for (auto& tower : m_divRootTowers)
		{
			tower->setbIsClickedOn(false);
		}
		for (auto& tower : m_subAddTowers)
		{
			tower->setbIsClickedOn(false);
		}
	}
}

void TowerManager::m_handleEvent_TowerSelection_LoopTowers(const sf::RenderWindow& window,
	std::vector<std::unique_ptr<Tower>>* towersVector)
{
	for (unsigned int i = 0; i < towersVector->size(); i++)
	{
		if (distanceBetweenPoints(towersVector->at(i)->getPosition(), window.mapPixelToCoords(sf::Mouse::getPosition(window))) <
			towersVector->at(i)->getRadius())
		{
			if (towersVector->at(i)->getbIsClickedOn()) // tower that was selected has been clicked on again
			{
				m_bTowerWasJustSelected = false; // in fact, a tower was just deselected
				towersVector->at(i)->setbIsClickedOn(false); // redundant, b/c all towers will be set clicked=false outside the function
				break; // a tower that was selected has been deselected; no need to do anything else with the existing towers
			}
			else
			{
				m_bTowerWasJustSelected = true;
				towersVector->at(i)->setbIsClickedOn(true);
				
				// deselect all towers (in current vector of towers) except the one that was just selected
				for (unsigned int k = 0; k < towersVector->size(); k++)
				{
					if (k != i)
					{
						towersVector->at(k)->setbIsClickedOn(false);
					}
				}
			}
		}
	}
}


// TODO: possibly rewrite this to accommodate a single vector of towers, and to create towers that
// are the correct subclass (subTower, divTower, rootTower)
void TowerManager::m_handleEvent_InsertDummyTowerIntoVectorOfTowers(const sf::RenderWindow& window)
{
	if (m_dummyTower.getAttackType() == attackType::subtract)
	{
		bool bTowerInsertedIntoVector = false;
		int i_ = 0;
		while (!bTowerInsertedIntoVector) // go through subAddTowers from front to back to find the position at which to place new tower
		{
			if (i_ == m_subAddTowers.size()) // this is true if vector was previously empty, or if we reach the end of the vector
			{ 
				// TODO: NOTE THIS CHANGE THAT WAS MADE, TESTING TowerSub CONSTRUCTION (also a few lines down)
				
				m_subAddTowers.push_back(std::make_unique<TowerSub>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
				//m_subAddTowers.push_back(std::make_unique<Tower>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
				bTowerInsertedIntoVector = true; // leave the while loop
			}
			else if (m_dummyTower.getStrength() >= m_subAddTowers.at(i_)->getStrength())
			{
				// there are already some towers in the vector
				m_subAddTowers.insert(m_subAddTowers.begin() + i_,
					std::make_unique<TowerSub>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
					//std::make_unique<Tower>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
				bTowerInsertedIntoVector = true;
			}
			else
			{
				i_++;
			}
		}
	}
	else // we know attack type is either divide or root
	{
		bool bTowerInsertedIntoVector = false;
		int i_ = 0;
		while (!bTowerInsertedIntoVector) // go through divRootTowers from front to back to find the position at which to place new tower
		{
			if (i_ == m_divRootTowers.size()) // this is true if vector was previously empty, or if we reach the end of the vector
			{
				if (m_dummyTower.getAttackType() == attackType::divide)
				{
					m_divRootTowers.push_back(std::make_unique<TowerDiv>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
				}
				else
				{
					m_divRootTowers.push_back(std::make_unique<TowerRoot>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
				}
				
				bTowerInsertedIntoVector = true; // leave the while loop
			}
			else if (m_dummyTower.getAttackType() == attackType::root)
			{
				if (m_divRootTowers.at(i_)->getAttackType() == attackType::divide)
				{
					// we have reached the first divide tower, so place the new root tower before it
					m_divRootTowers.insert(m_divRootTowers.begin() + i_,
						std::make_unique<TowerRoot>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
					bTowerInsertedIntoVector = true;
					// note that the above .insert line is written 3 times in this section in different if statements for
					// clarity of code, instead of writing them only once
				}
				else if (m_dummyTower.getStrength() >= m_divRootTowers.at(i_)->getStrength()) // comparing with a root tower
				{
					// reached an existing root tower of equal or lesser strength, so place the new root tower before it
					m_divRootTowers.insert(m_divRootTowers.begin() + i_,
						std::make_unique<TowerRoot>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
					bTowerInsertedIntoVector = true;
				}
				else
				{
					// the root tower cannot be placed here, so advance to look at the next spot
					i_++;
				}
			}
			else if (m_dummyTower.getAttackType() == attackType::divide) // at this point the new tower MUST be a divide tower
			{
				if (m_divRootTowers.at(i_)->getAttackType() == attackType::divide &&
					m_dummyTower.getStrength() >= m_divRootTowers.at(i_)->getStrength())
				{
					m_divRootTowers.insert(m_divRootTowers.begin() + i_,
						std::make_unique<TowerDiv>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
					bTowerInsertedIntoVector = true;
				}
				else
				{
					// the only way we place a new divide tower is if the tower that follows is also divide of equal or lesser strength
					i_++;
				}
			}
		}
	}
}


