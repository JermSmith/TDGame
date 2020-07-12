#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <memory>

#include "Path.h"
#include "Enemy.h"
#include "ProjectileManager.h"
#include "Util\AttackTypes.h"

#include "GUI\StackMenu.h"
#include "GUI\HoverMenu.h"
#include "GUI\Button.h"
#include "GUI\Banner.h"

class Tower : public InteractableShape
{
public:
	Tower(const sf::RenderWindow& window); // cursor uses this constructor
	Tower(const sf::RenderWindow& window, const attackType& type, int strength, const sf::Vector2f& position, float radius, int pointCount);

	// sets AttackType, Strength, Position, Radius, and Range, as well as colours/outlines
	void setBasicProperties(attackType type, int strength, sf::Vector2f position, float radius, int pointCount);

	void handleEvent(sf::Event e, const sf::RenderWindow& window);

	virtual void updateAtakTimer_FindEnems_CreateProj(const std::vector<std::unique_ptr<Enemy>>& enemies);
	void updateProjectiles(std::vector<std::unique_ptr<Enemy>>& enemies);
	void updateAppearanceAndMenus(const sf::RenderWindow& window);
	void render(sf::RenderTarget& renderer);

	const sf::Vector2f& getPosition() const;
	void setPosition(sf::Vector2f& position);

	float getRadius() const;

	const attackType& getAttackType() const;
	void setAttackType(attackType&);

	float getRange() const;
	void setRange(const float);

	int getStrength() const;
	void setStrength(const int);

	bool getbIsClickedOn() const;
	void setbIsClickedOn(const bool);

protected:
	// these are accessible by TowerSub/Div/Root and Cursor, but not others

	sf::Vector2f m_position;
	int m_strength = 1; // meaningless initialization
	float m_range = 0; // meaningless initialization
	float m_projSpeed = 8.f;

	sf::CircleShape m_rangeCircle;
	sf::Text m_strengthString;

	sf::Clock m_timer;
	sf::Time m_timeElapsedSinceAttack;
	sf::Time m_timeOfLastAttack = m_timer.restart();
	sf::Time m_cooldownTime;
	bool m_bShouldResetElapsedTime = false;

	int m_lastWaveNumProjFired = 0;
	int m_lifetimeNumProjFired = 0;
	int m_lastWaveDmg = 0;
	int m_lifetimeDmg = 0;
	int m_lastWaveKillcount = 0;
	int m_lifetimeKillcount = 0;

	enum class targetPriority
	{
		close,
		first,
		last,
		strong,
		weak,
		largestPrime,
	};

	attackType m_attackType = attackType::subtract; // meaningless initialization
	targetPriority m_priority = targetPriority::first; // meaningless initialization
	unsigned int m_maxNumTargets = 1; // meaningless initialization
	unsigned int m_defaultMaxNumTargets = 1;
	float m_defaultProjSpeed = 8.f;

	/* Before this function is called, the enemy in "enemies" at the index "enemyIndex" must be known to be in range of
	the tower and attackable by the attack type. Then the function either slots "enemyIndex" into the "enemyIndicesToAttack"
	vector at the proper position to maintain the sorting of most prioritized towers to least prioritized towers in the vector,
	or else it does not change "enemyIndices" if the enemy does not exceed priority criteria. Returns vector of enemy indices. */
	std::vector<int> m_possiblyAddEnemyIndexToVectorAndSort(const std::vector<std::unique_ptr<Enemy>>& enemies, int enemyIndex, std::vector<int> enemyIndicesToAttack);

	ProjectileManager m_projectileManager;

	bool m_bIsClickedOn = true;

	// vv MENUS vv

	virtual void generateWidgets(const sf::RenderWindow&) = 0;

	virtual void populateHoverMenu() = 0; // defined in subclasses
	virtual void populateUpgradeMenu() = 0;
	//virtual void populatePriorityMenu() = 0;
	//virtual void populateStatsMenu() = 0;

	gui::HoverMenu m_hoverMenu;
	gui::StackMenu m_upgradeMenu;
	gui::StackMenu m_priorityMenu;
	gui::StackMenu m_statsMenu;

	gui::Banner bnrCursorNote = gui::makeBanner(gui::ButtonSizes::HOVER_W, gui::ButtonSizes::HOVER_H);

	// HOVER MENU

	gui::Banner bnrRange = gui::makeBanner(gui::ButtonSizes::HOVER_W, gui::ButtonSizes::HOVER_H);
	gui::Banner bnrCooldown = gui::makeBanner(gui::ButtonSizes::HOVER_W, gui::ButtonSizes::HOVER_H);
	gui::Banner bnrProjSpeed = gui::makeBanner(gui::ButtonSizes::HOVER_W, gui::ButtonSizes::HOVER_H);
	gui::Banner bnrNumTargets = gui::makeBanner(gui::ButtonSizes::HOVER_W, gui::ButtonSizes::HOVER_H);
	gui::Banner bnrPriority = gui::makeBanner(gui::ButtonSizes::HOVER_W, gui::ButtonSizes::HOVER_H);

	// UPGRADE MENU

	// TODO: possibly make the button sizes into vectors
	gui::Button btnUpgrade1 = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnUpgrade2 = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnUpgrade3 = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnUpgrade4 = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnSetPriority = gui::makeButton(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);

	// PRIORITY MENU

	// TODO: make new button sizes for priority buttons
	gui::Button btnPriClose = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnPriFirst = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnPriLast = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnPriStrong = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnPriWeak = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);
	gui::Button btnPriLgPrime = gui::makeButton(gui::ButtonSizes::RECT_SM_W, gui::ButtonSizes::RECT_SM_H);

	// STATS MENU

	gui::Banner bnrLastWaveNumProj = gui::makeBanner(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Banner bnrLifetimeNumProj = gui::makeBanner(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Banner bnrLastWaveDmg = gui::makeBanner(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Banner bnrLifetimeDmg = gui::makeBanner(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H);
	gui::Banner bnrLastWaveKills = gui::makeBanner(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H); // only for sub tower
	gui::Banner bnrLifetimeKills = gui::makeBanner(gui::ButtonSizes::RECT_LG_W, gui::ButtonSizes::RECT_LG_H); // only for sub tower

private:
	void m_hideHoverMenu();
	void m_hideUpgradeMenu();
	void m_hidePriorityMenu();
	void m_hideStatsMenu();
};


