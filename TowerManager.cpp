#include "TowerManager.h"

TowerManager::TowerManager()
{

}

void TowerManager::update(const sf::RenderWindow& window, const Path& path, std::vector<std::unique_ptr<Enemy>>* enemies)
{
	//for (unsigned int i = 0; i < m_towers.size(); i++)
	for (auto& tower : m_towers)
	{
		//m_towers.at(i)->update(enemies);
		tower->update(enemies);
	}

	m_dummyTower.update(window, m_bTowerBeingPlaced, m_towers, path);
}

void TowerManager::handleEvent(sf::Event e, const sf::RenderWindow& window, const Path& path)
{
	if (e.type == sf::Event::EventType::MouseButtonReleased)
	{
		bool bThereExistsASelectedTower = false;
		for (unsigned int i = 0; i < m_towers.size(); i++)
		{
			if (distanceBetweenPoints(m_towers.at(i)->getPosition().x, m_towers.at(i)->getPosition().y,
				window.mapPixelToCoords(sf::Mouse::getPosition(window)).x, window.mapPixelToCoords(sf::Mouse::getPosition(window)).y) <
				m_towers.at(i)->getRadius())
			{
				if (m_towers.at(i)->getbIsClickedOn())
				{
					bThereExistsASelectedTower = false;
					m_towers.at(i)->setbIsClickedOn(false);
					break; // a tower that was selected has been deselected; no need to do anything else with the existing towers
				}
				else
				{
					bThereExistsASelectedTower = true;
					m_towers.at(i)->setbIsClickedOn(true);
					for (unsigned int k = 0; k < m_towers.size(); k++)
					{
						if (k != i)
						{
							m_towers.at(k)->setbIsClickedOn(false);
						}
					}
				}
			}
		}

		if (!bThereExistsASelectedTower)
		{
			for (auto& tower : m_towers)
			{
				tower->setbIsClickedOn(false);
			}
		}

		if (m_bTowerBeingPlaced)
		{
			// place dummy tower at mouse position to check for interference
			m_dummyTower.setPosition(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

			if (!m_dummyTower.bInterferesWithScene(m_towers, path, window))
			{
				//no interference found with new object and path, so can place object
				m_towers.push_back(std::make_unique<Tower>(window, m_dummyTower.getAttackType(), m_dummyTower.getStrength()));
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

std::vector<std::unique_ptr<Tower>>* TowerManager::getTowers()
{
	return &m_towers;
}

Cursor* TowerManager::getDummyTower()
{
	return &m_dummyTower;
}

const bool& TowerManager::getbTowerBeingPlaced() const
{
	return m_bTowerBeingPlaced;
}

void TowerManager::setbTowerBeingPlaced(bool tf)
{
	m_bTowerBeingPlaced = tf;
}


