#include "TowerManager.h"
#include <iostream>

// TODO: find somewhere in the code (probably create a new class or two) to manage the store, inventory and world.
// store is the available towers; inventory is towers that have been purchased/accumulated; world is what has been placed along the path.
// towers go from store --> inventory --> world

// TODO: make it so there is a money system for the store (maybe?) BUT definitely a "points system" in the playing space, 
// where you can only place up to a certain total "value" of towers in the space (diff. towers taking more or less value)

// TODO: implement sell tower, move tower, etc. buttons when tower is clicked on

TowerManager::TowerManager()
{

}

void TowerManager::update(const sf::RenderWindow& window, const Path& path, std::vector<std::unique_ptr<Enemy>>* enemies)
{
	m_dummyTower.update(window, path, m_towers, m_bTowerBeingPlaced);

	for (auto& tower : m_towers)
	{
		// each time a div tower is updated, we update all root towers
		// each time a sub tower is updated, we update all div/root towers
		// consider the situation where sqrt, /2 and -1 all want to attack "32":
		// if not using these nested loops, then sqrt can't attack -> 32/2 = 16 -> 16-1=15 -> sqrt still can't attack

		tower->updateAttackLogic(enemies); // each tower is updated
		
		if (tower->getAttackType() == attackType::divide) // e.g. 32 is invulnerable to sqrt, but not after "/2"
		{
			for (auto& t_r : m_towers) // update all root towers
			{
				if (t_r->getAttackType() == attackType::root)
				{
					t_r->updateAttackLogic(enemies);
				}
			}
		}
		
		else if (tower->getAttackType() == attackType::subtract) // e.g. 17 is invulnerable to sqrt, but not after "-1"
		{
			for (auto& tow : m_towers)
			{
				if (tow->getAttackType() != attackType::subtract) // tow is either root or div tower
				{
					tow->updateAttackLogic(enemies);

					if (tow->getAttackType() == attackType::divide) // e.g. 33 is invulnerable to sqrt, but not after "-1" then "/2"
					{
						for (auto& t_r : m_towers) // update all root towers
						{
							if (t_r->getAttackType() == attackType::root)
							{
								t_r->updateAttackLogic(enemies);
							}
						}
					}
				}
			}
		}

		tower->updateProjectiles(enemies);
		tower->updateAppearance(window);
	}
}

void TowerManager::handleEvent(sf::Event e, const sf::RenderWindow& window, const Path& path)
{
	if (e.type == sf::Event::EventType::MouseButtonReleased)
	{
		sf::Vector2f clickPos = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		m_handleEvent_TowerSelection(clickPos);

		if (m_bTowerBeingPlaced)
		{
			// place dummy tower at mouse position to check for interference
			m_dummyTower.setPosition(clickPos);

			if (!m_dummyTower.bInterferesWithScene(m_towers, path))
			{
				//no interference found with new tower and path, so can place tower
				
				m_handleEvent_InsertDummyTowerIntoVectorOfTowers();
				// Note that strongest towers are placed closer to front of vector, so they are updated first:
				// root4 > sqrt > /13 > /2 > -2 > -1 > +1 > +2

				m_bTowerBeingPlaced = false;
			}
		}
	}
}

void TowerManager::render(sf::RenderTarget& renderer)
{
	for (const auto& obj : m_towers)
	{
		obj->render(renderer);
	}

	m_dummyTower.render(renderer);
}

void TowerManager::reset()
{
	m_towers.clear();
}

Cursor* TowerManager::getDummyTower() { return &m_dummyTower; }

const bool& TowerManager::getbTowerBeingPlaced() const
{
	return m_bTowerBeingPlaced;
}

void TowerManager::setbTowerBeingPlaced(bool tf)
{
	m_bTowerBeingPlaced = tf;
}

// This function is entered at every click event. It determines whether or not a tower was
// clicked on, and modifies the "isClickedOn" property of all towers accordingly.
void TowerManager::m_handleEvent_TowerSelection(const sf::Vector2f& clickPos)
{
	bool bClickedOffOfTower = true; // will remain true unless a tower is found that was clicked on

	for (unsigned int i = 0; i < m_towers.size(); i++)
	{
		if (distanceBetweenPoints(m_towers.at(i)->getPosition(), clickPos) < m_towers.at(i)->getRadius())
			// then the tower at position i is the tower that has been clicked on
		{
			bClickedOffOfTower = false; // false, because we have seen that the click was ON a tower

			if (m_towers.at(i)->getbIsClickedOn()) // tower that was selected has been clicked on again
			{
				m_towers.at(i)->setbIsClickedOn(false);
				break; // a tower that was selected has been deselected; no need to do anything else with the existing towers
			}
			else // the clicked tower was not previously selected, so deselect any prev. selected towers and select the one at i
			{
				// deselect all towers...
				for (unsigned int k = 0; k < m_towers.size(); k++)
				{
					m_towers.at(k)->setbIsClickedOn(false);
				}
				// ...then select the new one
				m_towers.at(i)->setbIsClickedOn(true);
			}
		}
	}

	if (bClickedOffOfTower)
	{
		for (unsigned int k = 0; k < m_towers.size(); k++)
		{
			m_towers.at(k)->setbIsClickedOn(false);
		}
	}
}

// the dummy tower holds attack type and strength (and a few other properties) of the tower to be placed
void TowerManager::m_handleEvent_InsertDummyTowerIntoVectorOfTowers()
{
	bool bTowerInsertedIntoVector = false;

	if (m_towers.size() == 0) // first tower to be added
	{
		switch (m_dummyTower.getAttackType())
		{
		case attackType::root:
			m_towers.push_back(std::make_unique<TowerRoot>
				( m_dummyTower.getAttackType()
				, m_dummyTower.getStrength()
				, m_dummyTower.getPosition()
				, m_dummyTower.getRadius()
				, m_dummyTower.getPointCount()));
			break;
		case attackType::divide:
			m_towers.push_back(std::make_unique<TowerDiv>
				( m_dummyTower.getAttackType()
				, m_dummyTower.getStrength()
				, m_dummyTower.getPosition()
				, m_dummyTower.getRadius()
				, m_dummyTower.getPointCount()));
			break;
		case attackType::subtract:
			m_towers.push_back(std::make_unique<TowerSub>
				( m_dummyTower.getAttackType()
				, m_dummyTower.getStrength()
				, m_dummyTower.getPosition()
				, m_dummyTower.getRadius()
				, m_dummyTower.getPointCount()));
			break;
		}
		return; // leave the function
	}

	else if (m_dummyTower.getAttackType() == attackType::root)
	{
		unsigned int i_wh = 0;
		while (!bTowerInsertedIntoVector)
		{
			if (m_towers.size() == i_wh) // iterator has gone out of range (i.e. reached the end of the vector)
				// (and as a result, there must only be root towers in the vector)
			{
				m_towers.push_back(std::make_unique<TowerRoot>
					( m_dummyTower.getAttackType()
					, m_dummyTower.getStrength()
					, m_dummyTower.getPosition()
					, m_dummyTower.getRadius()
					, m_dummyTower.getPointCount()));
				bTowerInsertedIntoVector = true;
			}
			else
			{
				switch (m_towers.at(i_wh)->getAttackType())
				{
				case attackType::root:
					if (m_towers.at(i_wh)->getStrength() > m_dummyTower.getStrength())
					{
						i_wh++; // look to the next spot in the vertex
					}
					else if (m_towers.at(i_wh)->getStrength() <= m_dummyTower.getStrength()) // equivalent to ELSE
					{
						m_towers.insert(m_towers.begin() + i_wh,
							std::make_unique<TowerRoot>
								( m_dummyTower.getAttackType()
								, m_dummyTower.getStrength()
								, m_dummyTower.getPosition()
								, m_dummyTower.getRadius()
								, m_dummyTower.getPointCount()));
						bTowerInsertedIntoVector = true;
					}
					break;

				case attackType::divide:
					m_towers.insert(m_towers.begin() + i_wh,
						std::make_unique<TowerRoot>
							( m_dummyTower.getAttackType()
							, m_dummyTower.getStrength()
							, m_dummyTower.getPosition()
							, m_dummyTower.getRadius()
							, m_dummyTower.getPointCount()));
					bTowerInsertedIntoVector = true;
					break; // placed the first root tower before the strongest div tower

				case attackType::subtract:
					m_towers.insert(m_towers.begin() + i_wh,
						std::make_unique<TowerRoot>
							( m_dummyTower.getAttackType()
							, m_dummyTower.getStrength()
							, m_dummyTower.getPosition()
							, m_dummyTower.getRadius()
							, m_dummyTower.getPointCount()));
					bTowerInsertedIntoVector = true;
					break; // placed the first root tower before the strongest sub tower
				}
			}
		}
	}

	else if (m_dummyTower.getAttackType() == attackType::divide)
	{
		unsigned int j_wh = 0;
		while (!bTowerInsertedIntoVector)
		{
			if (m_towers.size() == j_wh) // iterator has gone out of range (i.e. reached the end of the vector)
			{
				m_towers.push_back(std::make_unique<TowerDiv>
					( m_dummyTower.getAttackType()
					, m_dummyTower.getStrength()
					, m_dummyTower.getPosition()
					, m_dummyTower.getRadius()
					, m_dummyTower.getPointCount()));
				bTowerInsertedIntoVector = true;
			}
			else
			{
				switch (m_towers.at(j_wh)->getAttackType())
				{
				case attackType::root:
					j_wh++; // cannot place a div tower before a root tower
					break;

				case attackType::divide:
					if (m_towers.at(j_wh)->getStrength() > m_dummyTower.getStrength())
					{
						j_wh++;
					}
					else if (m_towers.at(j_wh)->getStrength() <= m_dummyTower.getStrength()) // equivalent to ELSE
					{
						m_towers.insert(m_towers.begin() + j_wh,
							std::make_unique<TowerDiv>
								( m_dummyTower.getAttackType()
								, m_dummyTower.getStrength()
								, m_dummyTower.getPosition()
								, m_dummyTower.getRadius()
								, m_dummyTower.getPointCount()));
						bTowerInsertedIntoVector = true;
					}
					break;

				case attackType::subtract:
					m_towers.insert(m_towers.begin() + j_wh,
						std::make_unique<TowerDiv>
							( m_dummyTower.getAttackType()
							, m_dummyTower.getStrength()
							, m_dummyTower.getPosition()
							, m_dummyTower.getRadius()
							, m_dummyTower.getPointCount()));
					bTowerInsertedIntoVector = true;
					break; // place first div tower immediately before strongest sub tower
				}
			}
		}
	}

	else if (m_dummyTower.getAttackType() == attackType::subtract)
	{
		unsigned int k_wh = 0;
		while (!bTowerInsertedIntoVector)
		{
			if (m_towers.size() == k_wh) // iterator has gone out of range (i.e. reached the end of the vector)
			{
				m_towers.push_back(std::make_unique<TowerSub>
					( m_dummyTower.getAttackType()
					, m_dummyTower.getStrength()
					, m_dummyTower.getPosition()
					, m_dummyTower.getRadius()
					, m_dummyTower.getPointCount()));
				bTowerInsertedIntoVector = true;
			}
			else
			{
				switch (m_towers.at(k_wh)->getAttackType())
				{
				case attackType::root:
					k_wh++; // look at the next spot in the vector, since sub tower can't go before root
					break;

				case attackType::divide:
					k_wh++; // look at the next spot in the vector, since sub tower can't go before div
					break;

				case attackType::subtract:
					if (m_towers.at(k_wh)->getStrength() > m_dummyTower.getStrength()) // note: "sub 5" has strength 5.. "add 1" has strength -1
					{
						k_wh++;
					}
					else if (m_towers.at(k_wh)->getStrength() <= m_dummyTower.getStrength()) // equivalent to ELSE
					{
						m_towers.insert(m_towers.begin() + k_wh,
							std::make_unique<TowerSub>
								( m_dummyTower.getAttackType()
								, m_dummyTower.getStrength()
								, m_dummyTower.getPosition()
								, m_dummyTower.getRadius()
								, m_dummyTower.getPointCount()));
						bTowerInsertedIntoVector = true;
					}
					break;
				}
			}
		}
	}
}



