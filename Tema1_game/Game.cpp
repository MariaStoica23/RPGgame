#include "GameManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

GameManager* GameManager::instance = nullptr;
const int GameManager::enemiesCount = 15;

GameManager* GameManager::getInstance() {
	if (instance == nullptr)
		instance = new GameManager();
	return instance;
}

void GameManager::initialize() {
	std::ifstream file("file.in");
	file >> mainCharacter;
	for (int i = 0; i < enemiesCount; i++) {
		Character currentEnemy;
		file >> currentEnemy;
		enemies.push_back(currentEnemy);
	}
	file.close();
}

Character& GameManager::getMainCharacter() {
	return mainCharacter;
}

std::vector<Character>& GameManager::getEnemies() {
	return enemies;
}

void GameManager::setMainCharacter(const Character& mainCharacter) {
	this->mainCharacter = mainCharacter;
}

void GameManager::setEnemies(const std::vector<Character>& enemies) {
	for (int i = 0; i < enemies.size(); i++) {
		this->enemies[i] = enemies[i];
	}
}

std::string GameManager::getMainCharacterName() const {
	return mainCharacter.getName();
}

int GameManager::getMainCharacterLvl() const {
	return mainCharacter.getLvl();
}

int GameManager::getMainCharacterAttackDamage() const {
	return mainCharacter.getAttackDamage();
}

int GameManager::getMainCharacterDefence() const {
	return mainCharacter.getDefence();
}

int GameManager::getMainCharacterHealthPoints() const {
	return mainCharacter.getHealthPoints();
}

int GameManager::getMainCharacterRemainingHealthPoints() const {
	return mainCharacter.getRemainingHealthPoints();
}

int GameManager::getMainCharacterHealthPotionsCount() const {
	return mainCharacter.getHealthPotionsCount();
}

int GameManager::getEnemyHealthPoints(const int& index) const {
	if (index < 0 || index >= enemies.size())
		throw "Enemy index out of range";
	return enemies[index].getHealthPoints();
}

int GameManager::getEnemyRemainingHealthPoints(const int& index) const {
	if (index < 0 || index >= enemies.size())
		throw "Enemy index out of range";
	return enemies[index].getRemainingHealthPoints();
}

void GameManager::healMainCharacter() {
	mainCharacter.heal();
}

void GameManager::mainCharacterAttackEnemy(const int& index) {
	if (index < 0 || index >= enemies.size())
		throw "Enemy index out of range";
	mainCharacter.attack(enemies[index]);
}

void GameManager::enemyAttackMainCharacter(const int& index) {
	if (index < 0 || index >= enemies.size())
		throw "Enemy index out of range";
	enemies[index].attack(mainCharacter);
}

bool GameManager::isGameOver() const {
	return !mainCharacter.isAlive();
}

bool GameManager::isMainCharacterAlive() const {
	return mainCharacter.isAlive();
}

bool GameManager::isEnemyAlive(const int& index) const {
	if (index < 0 || index >= enemies.size())
		throw "Enemy index out of range";
	return enemies[index].isAlive();
}
