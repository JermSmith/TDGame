#include "Tower.h"
#include "Util\Math.h"
#include "ResourceManager\ResourceHolder.h"
#include "Util\ColourManager.h"
#include <algorithm>

Tower::Tower(const sf::RenderWindow& window) // for cursor
	:
	InteractableShape(0.f, 0)
	,
	m_hoverMenu(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)))
		, (float)sizes::HOVERMENU_X
		, 1.f, 50)
	,
	m_statsMenu(sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 250)
		, (float)sizes::PLAYINGMENU_X
		, 2.f, 155)
{}

Tower::Tower(const sf::RenderWindow& window, const attackType& type, int strength, const sf::Vector2f& position
	, float radius, int pointCount) // for placed towers
	:
	InteractableShape(radius, pointCount)
	,
	m_hoverMenu(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window)))
		, (float)sizes::HOVERMENU_X
		, 1.f, 50)
	,
	m_statsMenu(sf::Vector2f((float)sizes::WORLD_SIZE_X - (float)sizes::PLAYINGMENU_X / 2.0f, 250)
		, (float)sizes::PLAYINGMENU_X
		, 2.f, 155)
{
	setBasicProperties(type, strength, position, radius, pointCount);
}

void Tower::setBasicProperties(attackType type, int strength, sf::Vector2f position, float radius, int pointCount)
{
	m_position = position; //position where the mouse is clicked; want this to be centre of circle
	m_attackType = type;
	m_strength = strength;
	InteractableShape::defineShape(radius, pointCount);
	// radius set in InteractableShape::defineShape in Cursor.cpp
	
	switch (m_attackType) // Cursor reads radius and range from this function when previewing tower placement
	{
	case attackType::subtract:
		m_range = 333.33333f;
		m_cooldownTime = sf::milliseconds(2121);
		m_priority = targetPriority::close;
		m_maxNumTargets = m_defaultMaxNumTargets;
		m_projSpeed = m_defaultProjSpeed;

		if (m_strength < 0) { m_strengthString.setString("+ " + std::to_string(m_strength)); }
		else { m_strengthString.setString("- " + std::to_string(m_strength)); }
		break;

	case attackType::divide:
		m_range = 512.345678f;
		m_cooldownTime = sf::milliseconds(999);
		m_priority = targetPriority::close;
		m_maxNumTargets = m_defaultMaxNumTargets;
		m_projSpeed = m_defaultProjSpeed;

		m_strengthString.setString("/ " + std::to_string(m_strength));
		break;

	case attackType::root:
		m_range = 223.45678f;
		m_cooldownTime = sf::milliseconds(500);
		m_priority = targetPriority::strong;
		m_maxNumTargets = m_defaultMaxNumTargets;
		m_projSpeed = 12.66666f;

		if (m_strength == 2) { m_strengthString.setString("Sqrt"); }
		else if (m_strength == 3) { m_strengthString.setString("Cbrt"); }
		else { m_strengthString.setString(std::to_string(m_strength) + "th root"); }
		break;
	}

	//origin is relative to the top left corner of the circle's surrounding "box"
	InteractableShape::setPosition(m_position); //origin of the circle goes to this position, which is location of click
	InteractableShape::setFillColour(colours::selectRandomColor());

	m_rangeCircle.setRadius(m_range);
	m_rangeCircle.setOrigin(sf::Vector2f(m_range, m_range));
	m_rangeCircle.setPosition(m_position);
	m_rangeCircle.setFillColor(colours::towerRangeFillColour);

	// m_strengthString.setFontResourceHolder::get().fonts.get("stkaiti"));
	m_strengthString.setFont(ResourceHolder::get().fonts.get("arial"));
	m_strengthString.setPosition(sf::Vector2f(m_position.x - getPrimaryDim() / (float)2, m_position.y - getPrimaryDim() / (float)2));
	m_strengthString.setFillColor(colours::towerTextColour);
}

void Tower::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
	
}

void Tower::updateAtakTimer_FindEnems_CreateProj(const std::vector<std::unique_ptr<Enemy>>& enemies) {}

void Tower::updateProjectiles(std::vector<std::unique_ptr<Enemy>>& enemies)
{
	m_projectileManager.update(enemies);
}

void Tower::updateAppearance(const sf::RenderWindow& window)
{
	m_bUpdateAppearance(m_bIsClickedOn, InteractableShape::isRolledOn(window));
}

void Tower::render(sf::RenderTarget& renderer)
{
	renderer.draw(m_rangeCircle);
	InteractableShape::render(renderer);
	renderer.draw(m_strengthString);

	m_projectileManager.render(renderer);

	m_hoverMenu.render(renderer);
	m_statsMenu.render(renderer);
}

const sf::Vector2f& Tower::getPosition() const { return m_position; }
void Tower::setPosition(sf::Vector2f& position) { m_position = position; }

float Tower::getRadius() const { return getPrimaryDim(); }

const attackType& Tower::getAttackType() const { return m_attackType; }
void Tower::setAttackType(attackType& type) { m_attackType = type; }

float Tower::getRange() const { return m_range; }
void Tower::setRange(const float range) { m_range = range; }

int Tower::getStrength() const { return m_strength; }
void Tower::setStrength(const int strength) { m_strength = strength; }

bool Tower::getbIsClickedOn() const { return m_bIsClickedOn; }
void Tower::setbIsClickedOn(const bool tf) { m_bIsClickedOn = tf; }

void Tower::m_bUpdateAppearance(bool bIsClicked, bool bIsRolled)
{
	if (bIsClicked)
	{
		m_rangeCircle.setFillColor(sf::Color(255, 255, 255, 63));
		InteractableShape::setClickedAppearance();
		if (!m_statsMenu.bContainsWidgets())
		{
			populateStatsMenu();
		}
		
		// TODO: add line here for displaying tower stats/options-upgrade menu, e.g. m_infoAndUpdgradesMenu.display();
		// m_infoAndUpgradesMenu can contain banners that show lifetime damage dealt, last round damage dealt, 
		// (for sub towers lifetime/last round kills), stats such as type, strength, range, cooldown, num targets,
		// as well as upgrade buttons and priority buttons
	}
	else
	{
		m_rangeCircle.setFillColor(sf::Color::Transparent);
		InteractableShape::removeClickedAppearance();

		m_hideStatsMenu();
	}

	if (bIsRolled)
	{
		InteractableShape::setRolledAppearance();
		if (!m_hoverMenu.bContainsWidgets())
		{
			populateHoverMenu();
		}
	}
	else if (!bIsClicked) // enters here when NOT rolled and NOT clicked
	{
		InteractableShape::removeRolledAppearance();
	}
	
	if (!bIsRolled)
	{
		m_hideHoverMenu();
	}
}

void Tower::m_hideHoverMenu()
{
	m_hoverMenu.clearWidgets();
	m_hoverMenu.hideOutline();
}

void Tower::m_hideStatsMenu()
{
	m_statsMenu.clearWidgets();
	m_statsMenu.hideOutline();
}

/* Before this function is called, the enemy in "enemies" at the index "enemyIndex" must be known to be in range of
the tower and attackable by the attack type. Then the function either slots "enemyIndex" into the "enemyIndicesToAttack"
vector at the proper position to maintain the sorting of most prioritized towers to least prioritized towers in the vector,
or else it does not change "enemyIndices" if the enemy does not exceed priority criteria. Returns vector of enemy indices. */
std::vector<int> Tower::m_possiblyAddEnemyIndexToVectorAndSort(const std::vector<std::unique_ptr<Enemy>>& enemies, int a_enemyIndex, std::vector<int> a_enemyIndicesToAttack)
{
	int i_e = a_enemyIndex;
	std::vector<int> enemyIndicesToAttack = a_enemyIndicesToAttack;

	float enemyDistance; // used for "closest" priority

	switch (m_priority)
	{
	case targetPriority::close:
		/* The enemy indices are placed into "enemyIndicesToAttack" in such a way that the index at position 0 is the closest 
		enemy, and the index at position "maxNumTargets - 1" (or otherwise at the back, if num enemies in range is less than
		maxNumTargets) is the furthest enemy. This way, the furthest enemy can be easily popped if a closer enemy is found. */

		enemyDistance = distanceBetweenPoints(enemies.at(i_e)->getPosition(), m_position);

		if (enemyIndicesToAttack.size() == 0) // first enemy to be added
		{
			if (m_maxNumTargets != 0) // just in case
			{
				enemyIndicesToAttack.push_back(i_e);
			}
		}

		else if (enemyIndicesToAttack.size() < m_maxNumTargets)
		{// then any whichever index we check must be added into enemyIndices without removing any of them
			bool bIndexInsertedIntoVector = false;
			int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

			while (!bIndexInsertedIntoVector)
			{// compare distance of enemy (i_e) with distances of enemies already stored (j_v)
				if (j_v == enemyIndicesToAttack.size()) // the end of the vector
				{
					// insert i_e at the end of enemyIndices, since it represents the furthest enemy within range so far
					enemyIndicesToAttack.push_back(i_e);
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else if (enemyDistance < distanceBetweenPoints(enemies.at(enemyIndicesToAttack.at(j_v))->getPosition(), m_position))
				{
					/* if here, then the enemy being checked (not yet in index vector, at "enemyDistance" from tower) is closer to
					the tower than the enemy at position j_v in index vector */
					enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e); // insert index i_e at position j_v
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else
				{
					j_v++;
				}
			}
		}

		else if (enemyIndicesToAttack.size() == m_maxNumTargets)
			// the vector size is maxxed out, so the enemy will only be added if it is closer than the enemy at the currently-last index
		{
			/* On the following line, we perform a check that guarantees that the if statement inside the while loop that follows will
			eventually successfully add the new tower. Otherwise, the iterator for enemyIndicesToAttack will go out of range. */
			if (enemyDistance < distanceBetweenPoints(enemies.at(enemyIndicesToAttack.back())->getPosition(), m_position))
				// the vector will only change if enemy is closer than last enemy in enemyIndicesToAttack
			{
				bool bIndexInsertedIntoVector = false;
				int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

				while (!bIndexInsertedIntoVector)
				{// compare distance of enemy (i_e) with distances of enemies already stored (j_v)
					if (enemyDistance < distanceBetweenPoints(enemies.at(enemyIndicesToAttack.at(j_v))->getPosition(), m_position))
					{
						/* If here, then the distance from tower to enemy (enemyDistance) (not yet in index vector) is less than the
						distance from tower to enemy at position j_v (which is already in index vector), so add the new enemy, but that
						means the previously furthest enemy must be popped from the back of the vector, since vector is at capacity. */

						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e);
						// insert index i_e at position j_v (into enemyIndicesToAttack). Note: this could also be imm. before final element

						enemyIndicesToAttack.pop_back();
						/*remove the last element, since distance is too large -- the final index must be popped AFTER the insertion, not
						before, or else the insertion will be out of range in the case of inserting immediately before the final index */

						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						j_v++;
					}
				}
			}
		}
		break;

	case targetPriority::first:
		/* The enemy indices are placed into "enemyIndicesToAttack" in such a way that the index at position 0 is the smallest (i.e. most
		advanced enemy), and the index at position "maxNumTargets - 1" (or otherwise at the back, if num enemies in range is less than
		maxNumTargets) is the enemy with largest index. This way, the last enemy can be easily popped if an earlier enemy is found. */

		if (enemyIndicesToAttack.size() == 0) // first enemy to be added
		{
			if (m_maxNumTargets != 0) // just in case
			{
				enemyIndicesToAttack.push_back(i_e);
			}
		}

		else if (enemyIndicesToAttack.size() < m_maxNumTargets)
		{// then any whichever index we check must be added into enemyIndices without removing any of them
			bool bIndexInsertedIntoVector = false;
			int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

			while (!bIndexInsertedIntoVector)
			{// compare index of enemy (i_e) with the indices of enemies already stored
				if (j_v == enemyIndicesToAttack.size()) // the end of the vector
				{
					// insert i_e at the end of enemyIndices, since it represents the enemy of greatest index within range so far
					enemyIndicesToAttack.push_back(i_e);
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else if (i_e < enemyIndicesToAttack.at(j_v))
				{
					/* if here, then the index of the enemy being checked (i_e, not yet in index vector) is smaller than the index
					stored at position j_v in index vector */
					enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e); // insert index i_e at position j_v
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else
				{
					j_v++;
				}
			}
		}

		else if (enemyIndicesToAttack.size() == m_maxNumTargets)
			// the vector size is maxxed out, so the enemy will only be added if its index is lesser than the currently-last index in eITA
		{
			/* On the following line, we perform a check that guarantees that the if statement inside the while loop that follows will
			eventually successfully add the new tower. Otherwise, the iterator for enemyIndicesToAttack will go out of range. */
			if (i_e < enemyIndicesToAttack.back())
				// the vector will only change if enemy index is lesser than that of the last enemy in enemyIndicesToAttack
			{
				bool bIndexInsertedIntoVector = false;
				int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

				while (!bIndexInsertedIntoVector)
				{// compare index of enemy (i_e) with indices of enemies already stored (j_v)
					if (i_e < enemyIndicesToAttack.at(j_v))
					{
						/* If here, then the index i_e (not yet in index vector) is lesser than the index at position j_v (which is
						already in index vector), so add the new enemy, but that means the previously last enemy must be popped from
						the back of the vector, since vector is at capacity. */

						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e);
						// insert index i_e at position j_v (into enemyIndicesToAttack). Note: this could also be imm. before final element

						enemyIndicesToAttack.pop_back();
						/*remove the last element, since its index is too large -- the final index must be popped AFTER the insertion, not
						before, or else the insertion will be out of range in the case of inserting immediately before the final index */

						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						j_v++;
					}
				}
			}
		}

		break;

	case targetPriority::last:
		/* The enemy indices are placed into "enemyIndicesToAttack" in such a way that the index at position 0 is the largest (i.e. 
		furthest back enemy), and the index at position "maxNumTargets - 1" (or otherwise at the back, if num enemies in range is less 
		than maxNumTargets) is the enemy with smallest index. This way, the last enemy can be easily popped if a later enemy is found. */

		if (enemyIndicesToAttack.size() == 0) // first enemy to be added
		{
			if (m_maxNumTargets != 0) // just in case
			{
				enemyIndicesToAttack.push_back(i_e);
			}
		}

		else if (enemyIndicesToAttack.size() < m_maxNumTargets)
		{// then any whichever index we check must be added into enemyIndices without removing any of them
			bool bIndexInsertedIntoVector = false;
			int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

			while (!bIndexInsertedIntoVector)
			{// compare index of enemy (i_e) with the indices of enemies already stored
				if (j_v == enemyIndicesToAttack.size()) // the end of the vector
				{
					// insert i_e at the end of enemyIndices, since it represents the enemy of lowest index within range so far
					enemyIndicesToAttack.push_back(i_e);
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else if (i_e > enemyIndicesToAttack.at(j_v))
				{
					/* if here, then the index of the enemy being checked (i_e, not yet in index vector) is larger than the index
					stored at position j_v in index vector */
					enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e); // insert index i_e at position j_v
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else
				{
					j_v++;
				}
			}
		}

		else if (enemyIndicesToAttack.size() == m_maxNumTargets)
			// the vector size is maxxed out, so the enemy will only be added if its index is greater than the currently-last index in eITA
		{
			/* On the following line, we perform a check that guarantees that the if statement inside the while loop that follows will
			eventually successfully add the new tower. Otherwise, the iterator for enemyIndicesToAttack will go out of range. */
			if (i_e > enemyIndicesToAttack.back())
				// the vector will only change if enemy index is greater than that of the last enemy in enemyIndicesToAttack
			{
				bool bIndexInsertedIntoVector = false;
				int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

				while (!bIndexInsertedIntoVector)
				{// compare index of enemy (i_e) with indices of enemies already stored (j_v)
					if (i_e > enemyIndicesToAttack.at(j_v))
					{
						/* If here, then the index i_e (not yet in index vector) is greater than the index at position j_v (which is
						already in index vector), so add the new enemy, but that means the previously last enemy must be popped from
						the back of the vector, since vector is at capacity. */

						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e);
						// insert index i_e at position j_v (into enemyIndicesToAttack). Note: this could also be imm. before final element

						enemyIndicesToAttack.pop_back();
						/*remove the last element, since its index is too small -- the final index must be popped AFTER the insertion, not
						before, or else the insertion will be out of range in the case of inserting immediately before the final index */

						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						j_v++;
					}
				}
			}
		}

		break;

	case targetPriority::strong:
		/* The enemy indices are placed into "enemyIndicesToAttack" in such a way that the index at position 0 is the strongest
		enemy, and the index at position "maxNumTargets - 1" (or otherwise at the back, if num enemies in range is less than
		maxNumTargets) is the weakest enemy. This way, the weakest enemy can be easily popped if a stronger enemy is found.
		Note: if there are multiple enemies of the same greatest health, then tower attacks the one(s) that is most advanced,
		since the enemy healths are searched from first enemy to last enemy, and an enemy's health must be strictly greater than
		an existing enemy's health for it to be added to the vector of enemies to attack. */

		if (enemyIndicesToAttack.size() == 0) // first enemy to be added
		{
			if (m_maxNumTargets != 0) // just in case
			{
				enemyIndicesToAttack.push_back(i_e);
			}
		}

		else if (enemyIndicesToAttack.size() < m_maxNumTargets)
		{// then any whichever index we check must be added into enemyIndices without removing any of them
			bool bIndexInsertedIntoVector = false;
			int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

			while (!bIndexInsertedIntoVector)
			{// compare strength of enemy (i_e) with strengths of enemies already stored (j_v)
				if (j_v == enemyIndicesToAttack.size()) // the end of the vector
				{
					// insert i_e at the end of enemyIndices, since it represents the weakest enemy within range so far
					enemyIndicesToAttack.push_back(i_e);
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else if (enemies.at(i_e)->getHealth() > enemies.at(enemyIndicesToAttack.at(j_v))->getHealth())
				{
					/* if here, then the enemy being checked (not yet in index vector, at position i_e in enemies) is
					stronger than the enemy at position j_v in index vector, so gets put in */
					enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e); // insert index i_e at position j_v
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else
				{
					j_v++;
				}
			}
		}

		else if (enemyIndicesToAttack.size() == m_maxNumTargets)
			// the vector size is maxxed out, so the enemy will only be added if it is stronger than the enemy at the currently-last index
		{
			/* On the following line, we perform a check that guarantees that the if statement inside the while loop that follows will
			eventually successfully add the new tower. Otherwise, the iterator for enemyIndicesToAttack will go out of range. */
			if (enemies.at(i_e)->getHealth() > enemies.at(enemyIndicesToAttack.back())->getHealth())
				// the vector will only change if enemy is stronger than last enemy in enemyIndicesToAttack
			{
				bool bIndexInsertedIntoVector = false;
				int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

				while (!bIndexInsertedIntoVector)
				{// compare strength of enemy (i_e) with strengths of enemies already stored (j_v)
					if (enemies.at(i_e)->getHealth() > enemies.at(enemyIndicesToAttack.at(j_v))->getHealth())
					{
						/* If here, then the health of enemy being checked (not yet in index vector) is greater than the
						health of enemy at position j_v (which is already in index vector), so add the new enemy, but that
						means the previously weakest enemy must be popped from the back of the vector, since vector is at capacity. */

						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e);
						// insert index i_e at position j_v (into enemyIndicesToAttack). Note: this could also be imm. before final element

						enemyIndicesToAttack.pop_back();
						/*remove the last element, since health is too low -- the final index must be popped AFTER the insertion, not
						before, or else the insertion will be out of range in the case of inserting immediately before the final index */

						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						j_v++;
					}
				}
			}
		}
		break;

	case targetPriority::weak:
		/* The enemy indices are placed into "enemyIndicesToAttack" in such a way that the index at position 0 is the weakest
		enemy, and the index at position "maxNumTargets - 1" (or otherwise at the back, if num enemies in range is less than
		maxNumTargets) is the strongest enemy. This way, the strongest enemy can be easily popped if a weaker enemy is found.
		Note: if there are multiple enemies of the same lowest health, then tower attacks the one(s) that is most advanced,
		since the enemy healths are searched from first enemy to last enemy, and an enemy's health must be strictly less than
		an existing enemy's health for it to be added to the vector of enemies to attack. */

		if (enemyIndicesToAttack.size() == 0) // first enemy to be added
		{
			if (m_maxNumTargets != 0) // just in case
			{
				enemyIndicesToAttack.push_back(i_e);
			}
		}

		else if (enemyIndicesToAttack.size() < m_maxNumTargets)
		{// then any whichever index we check must be added into enemyIndices without removing any of them
			bool bIndexInsertedIntoVector = false;
			int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

			while (!bIndexInsertedIntoVector)
			{// compare strength of enemy (i_e) with strengths of enemies already stored (j_v)
				if (j_v == enemyIndicesToAttack.size()) // the end of the vector
				{
					// insert i_e at the end of enemyIndices, since it represents the strongest enemy within range so far
					enemyIndicesToAttack.push_back(i_e);
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else if (enemies.at(i_e)->getHealth() < enemies.at(enemyIndicesToAttack.at(j_v))->getHealth())
				{
					/* if here, then the enemy being checked (not yet in index vector, at position i_e in enemies) is
					weaker than the enemy at position j_v in index vector, so gets put in */
					enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e); // insert index i_e at position j_v
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else
				{
					j_v++;
				}
			}
		}

		else if (enemyIndicesToAttack.size() == m_maxNumTargets)
			// the vector size is maxxed out, so the enemy will only be added if it is stronger than the enemy at the currently-last index
		{
			/* On the following line, we perform a check that guarantees that the if statement inside the while loop that follows will
			eventually successfully add the new tower. Otherwise, the iterator for enemyIndicesToAttack will go out of range. */
			if (enemies.at(i_e)->getHealth() < enemies.at(enemyIndicesToAttack.back())->getHealth())
				// the vector will only change if enemy is weaker than last enemy in enemyIndicesToAttack
			{
				bool bIndexInsertedIntoVector = false;
				int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

				while (!bIndexInsertedIntoVector)
				{// compare strength of enemy (i_e) with strengths of enemies already stored (j_v)
					if (enemies.at(i_e)->getHealth() < enemies.at(enemyIndicesToAttack.at(j_v))->getHealth())
					{
						/* If here, then the health of enemy being checked (not yet in index vector) is less than the
						health of enemy at position j_v (which is already in index vector), so add the new enemy, but that
						means the previously strongest enemy must be popped from the back of the vector, since vector is at capacity. */

						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e);
						// insert index i_e at position j_v (into enemyIndicesToAttack). Note: this could also be imm. before final element

						enemyIndicesToAttack.pop_back();
						/*remove the last element, since health is too high -- the final index must be popped AFTER the insertion, not
						before, or else the insertion will be out of range in the case of inserting immediately before the final index */

						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						j_v++;
					}
				}
			}
		}
		break;

	case targetPriority::largestPrime:
		/* This target prioritization is only available to subtract towers, since divide towers and root towers cannot attack primes.
		The enemy indices are placed into "enemyIndicesToAttack" in such a way that the index at position 0 is the largest prime, 
		and the index at position "maxNumTargets - 1" (or otherwise at the back, if num enemies in range is less than maxNumTargets)
		is the weakest prime within range. If the vector is not filled to capacity with primes, then the remaining spots are filled
		with the furthest advanced non-primes. This way, if an enemy must be popped from the back of the vector to make space, it is
		either a prime that is too weak to be included or the non-prime that is furthest back for which there is room.
		Note: if there are multiple enemies of the same greatest prime health, then tower attacks the one(s) that is most advanced,
		since the enemies are searched from first enemy to last enemy, and an enemy's health must be strictly greater than
		an existing enemy's health for it to be added to the vector of enemies to attack. */

		bool bNewEnemyIsPrime = bIsPrime(enemies.at(i_e)->getHealth());

		if (enemyIndicesToAttack.size() == 0) // first enemy to be added
		{
			if (m_maxNumTargets != 0) // just in case
			{
				enemyIndicesToAttack.push_back(i_e);
			}
		}

		else if (enemyIndicesToAttack.size() < m_maxNumTargets)
		{// then any whichever index we check must be added into enemyIndices without removing any of them
			bool bIndexInsertedIntoVector = false;
			int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

			while (!bIndexInsertedIntoVector)
			{// compare primality of new enemy (i_e) with primalities of enemies already stored (j_v)
				if (j_v == enemyIndicesToAttack.size()) // the end of the vector
				{
					// insert i_e at the end of enemyIndices, since we couldn't add it earlier but vector still has room
					enemyIndicesToAttack.push_back(i_e);
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else if (bNewEnemyIsPrime && !bIsPrime(enemies.at(enemyIndicesToAttack.at(j_v))->getHealth()))
				{
					// new enemy is prime but existing enemy is not prime, so add the new enemy
					enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e); // insert index i_e at position j_v
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else if (!bNewEnemyIsPrime && bIsPrime(enemies.at(enemyIndicesToAttack.at(j_v))->getHealth()))
				{
					// new enemy is not prime but existing enemy is prime, so cannot add here
					j_v++;
				}
				else if (bNewEnemyIsPrime && bIsPrime(enemies.at(enemyIndicesToAttack.at(j_v))->getHealth()))
				{
					// the new enemy and existing enemy are both prime, so compare their health
					if (enemies.at(i_e)->getHealth() > enemies.at(enemyIndicesToAttack.at(j_v))->getHealth())
					{
						// new enemy is stronger, so add the new enemy
						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e); // insert index i_e at position j_v
						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						// existing enemy is stronger, so cannot add at this position
						j_v++;
					}
				}
				else if (!bNewEnemyIsPrime && !bIsPrime(enemies.at(enemyIndicesToAttack.at(j_v))->getHealth()))
				{
					// neither enemy is prime, so compare their position
					if (i_e < enemyIndicesToAttack.at(j_v))
					{
						// new enemy is further advanced (generated earlier..smaller index), so add the enemy
						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e); // insert index i_e at position j_v
						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						// existing enemy is further advanced, so cannot add at this position
						j_v++;
					}
				}
			}
		}

		else if (enemyIndicesToAttack.size() == m_maxNumTargets)
			/* the vector size is maxxed out, so the new enemy will only be added if it is a stronger prime than the last prime in the
			vector, or if it is further advanced than a non-prime in the vector */
		{
			bool bIndexInsertedIntoVector = false;
			int j_v = 0; // iterator for vector of indices (same as # of times while has looped)

			while (!bIndexInsertedIntoVector)
			{// compare primality of new enemy (i_e) with primalities of enemies already stored (j_v)
				if (j_v == enemyIndicesToAttack.size()) // reached the end of the vector
				{
					break; // exit the while - i_e will not be added to enemyIndices, since we couldn't find a place to add it
				}
				else if (bNewEnemyIsPrime && !bIsPrime(enemies.at(enemyIndicesToAttack.at(j_v))->getHealth()))
				{
					// new enemy is prime but existing enemy is not prime, so add the new enemy
					enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e);
					enemyIndicesToAttack.pop_back();
					bIndexInsertedIntoVector = true; // leave this while loop
				}
				else if (!bNewEnemyIsPrime && bIsPrime(enemies.at(enemyIndicesToAttack.at(j_v))->getHealth()))
				{
					// new enemy is not prime but existing enemy is prime, so cannot add here
					j_v++;
				}
				else if (bNewEnemyIsPrime && bIsPrime(enemies.at(enemyIndicesToAttack.at(j_v))->getHealth()))
				{
					// the new enemy and existing enemy are both prime, so compare their health
					if (enemies.at(i_e)->getHealth() > enemies.at(enemyIndicesToAttack.at(j_v))->getHealth())
					{
						// new enemy is stronger, so add the new enemy
						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e);
						enemyIndicesToAttack.pop_back();
						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						// existing enemy is stronger, so cannot add at this position
						j_v++;
					}
				}
				else if (!bNewEnemyIsPrime && !bIsPrime(enemies.at(enemyIndicesToAttack.at(j_v))->getHealth()))
				{
					// neither enemy is prime, so compare their position
					if (i_e < enemyIndicesToAttack.at(j_v))
					{
						// new enemy is further advanced (generated earlier..smaller index), so add the enemy
						enemyIndicesToAttack.insert(enemyIndicesToAttack.begin() + j_v, i_e);
						// insert index i_e at position j_v Note: this could also be imm. before final element
						enemyIndicesToAttack.pop_back();
						bIndexInsertedIntoVector = true; // leave this while loop
					}
					else
					{
						// existing enemy is further advanced, so cannot add at this position
						j_v++;
					}
				}
			}
		}
		break;
	}

	return enemyIndicesToAttack;
}





