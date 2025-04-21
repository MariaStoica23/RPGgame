#pragma once
#include <vector>
#include "Character.h"

class GameManager
{
public:
	static GameManager* getInstance();

	~GameManager() {};

	void initialize();

	Character& getMainCharacter();
	std::vector<Character>& getEnemies();

	void setMainCharacter(const Character& mainCharacter);
	void setEnemies(const std::vector<Character>& enemies);

	std::string getMainCharacterName() const;
	int getMainCharacterLvl() const;
	int getMainCharacterAttackDamage() const;
	int getMainCharacterDefence() const;
	int getMainCharacterHealthPoints() const;
	int getMainCharacterRemainingHealthPoints() const;
	int getMainCharacterHealthPotionsCount() const;

	int getEnemyHealthPoints(const int& index) const;
	int getEnemyRemainingHealthPoints(const int& index) const;

	void healMainCharacter();
	void mainCharacterAttackEnemy(const int& index);
	void enemyAttackMainCharacter(const int& index);

	bool isGameOver() const;
	bool isMainCharacterAlive() const;
	bool isEnemyAlive(const int& index) const;

public:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

private:
	GameManager() = default;

private:
	static GameManager* instance;
	static const int enemiesCount;

private:
	Character mainCharacter;
	std::vector<Character> enemies;
};

