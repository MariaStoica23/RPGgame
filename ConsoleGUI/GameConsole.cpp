#include "GameConsole.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

Game* Game::instance = nullptr;
const int Game::enemiesCount = 15;

const std::string Game::grass = Game::loadGrass("media/grass.txt");

std::vector<std::string> Game::mainCharacterDesign = Game::loadDrawing("media/mainCharacter.txt");

const std::vector<std::vector<std::string>> Game::enemiesDesign = { Game::loadDrawing("media/enemy1.txt"), Game::loadDrawing("media/enemy2.txt"), Game::loadDrawing("media/enemy3.txt") };

const std::vector<std::string> Game::gameOver = Game::loadDrawing("media/gameOver.txt");

const std::vector<std::string> Game::youWin = Game::loadDrawing("media/youWin.txt");

Game* Game::getInstance() {
	if (instance == nullptr)
		instance = new Game();
	return instance;
}

void Game::initialize() {
	manager = GameManager::getInstance();
	manager->initialize();
}

void Game::run() {
	std::sort(manager->getEnemies().begin(), manager->getEnemies().end());
	int index = 0, option;
	while (index < enemiesCount && manager->isMainCharacterAlive()) {
		printBattleScene(index);
		std::cin >> option;
		if (option == 1) {
			manager->mainCharacterAttackEnemy(index);
		}
		else if (option == 2) {
			if (manager->getMainCharacterHealthPotionsCount() > 0)
				manager->healMainCharacter();
			else {
				std::cout << "Looks like you don't have any healing potions left. You can only attack." << std::endl;
				system("pause");
				continue;
			}
		}
		else {
			std::cout << "Invalid option!" << std::endl;
			system("pause");
			continue;
		}
		if (!manager->isEnemyAlive(index)) {
			index++;
			if (index != 0 && index % 2 == 0)
				manager->getMainCharacter()++;
		}
		else
			manager->enemyAttackMainCharacter(index);
	}
	printGameEnd();
}

std::string Game::getHealthBar(const int& healtPoints, const int& remainingHealthPoints) {
	int width = 10;
	int filled = (remainingHealthPoints * width) / healtPoints;
	if (filled == 0 && remainingHealthPoints != 0)
		filled = 1;
	std::string bar = "[";
	bar += std::string(filled, '#');
	bar += std::string(width - filled, '_');
	bar += "]";
	return bar;
}

void Game::printBattleScene(const int& round) {
	system("cls");
	std::cout << std::left;
	std::cout << std::setw(30) << (manager->getMainCharacterName() + " (Lvl " + std::to_string(manager->getMainCharacterLvl()) + ")") << std::endl;
	std::cout << std::setw(30) << ("Attack: " + std::to_string(manager->getMainCharacterAttackDamage()) + " | Defence: " + std::to_string(manager->getMainCharacterDefence())) << std::endl;
	std::cout << std::setw(30) << ("Healing potions: " + std::to_string(manager->getMainCharacterHealthPotionsCount())) << std::endl;
	std::cout << std::setw(26) << ("HP: " + std::to_string(manager->getMainCharacterRemainingHealthPoints()) + "/" + std::to_string(manager->getMainCharacterHealthPoints()));
	std::cout << std::right << std::setw(20) << "HP: " << manager->getEnemyRemainingHealthPoints(round) << "/" << manager->getEnemyHealthPoints(round) << std::endl;
	std::cout << std::left << std::setw(26) << getHealthBar(manager->getMainCharacterHealthPoints(), manager->getMainCharacterRemainingHealthPoints());
	std::cout << std::right << std::setw(26) << getHealthBar(manager->getEnemyHealthPoints(round), manager->getEnemyRemainingHealthPoints(round)) << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < mainCharacterDesign.size(); i++) {
		std::cout << mainCharacterDesign[i];
		std::cout << std::right << std::setw(45) << enemiesDesign[round % enemiesDesign.size()][i];
		std::cout << std::endl;
	}
	std::cout << std::left << grass << std::endl;

	std::cout << std::endl;
	std::cout << "Oh no! It seems like the enemy wants to attack you." << std::endl;
	std::cout << "You have two option: " << std::endl;
	std::cout << "(1) - Attack the enemy" << std::endl << "(2) - Drink healing potion" << std::endl;
	std::cout << "What do you want to do? Enter your option: ";
}

void Game::printGameEnd()
{
	system("cls");
	if (manager->isGameOver()) {
		mainCharacterDesign[2][4] = 'X';
		mainCharacterDesign[2][6] = 'X';
		mainCharacterDesign[3][5] = 'O';

		std::cout << mainCharacterDesign[0] << std::endl;
		for (int i = 0; i < gameOver.size(); i++) {
			std::cout << mainCharacterDesign[i + 1];
			std::cout << "     ";
			std::cout << gameOver[i];
			std::cout << std::endl;
		}
		std::cout << mainCharacterDesign[mainCharacterDesign.size() - 2] << std::endl;
		std::cout << mainCharacterDesign[mainCharacterDesign.size() - 1] << std::endl;
		std::cout << grass << std::endl << std::endl;

		std::cout << "Oops! You died, your enemy was too strong." << std::endl << std::endl;
		std::cout << "Your final statul is: " << std::endl << manager->getMainCharacter();
	}
	else {
		mainCharacterDesign[2][4] = 'n';
		mainCharacterDesign[2][6] = 'n';
		mainCharacterDesign[3][5] = 'O';

		std::cout << mainCharacterDesign[0] << std::endl;
		for (int i = 0; i < youWin.size(); i++) {
			std::cout << mainCharacterDesign[i + 1];
			std::cout << "      ";
			std::cout << youWin[i];
			std::cout << std::endl;
		}
		std::cout << mainCharacterDesign[mainCharacterDesign.size() - 2] << std::endl;
		std::cout << mainCharacterDesign[mainCharacterDesign.size() - 1] << std::endl;
		std::cout << grass << std::endl << std::endl;

		std::cout << "Congratulation! You have defeated all enemies." << std::endl << std::endl;
		std::cout << "Your final statul is: " << std::endl << manager->getMainCharacter();
	}
}

std::string Game::loadGrass(const std::string& path) {
	std::string drawing;
	std::ifstream file(path);
	std::getline(file, drawing);
	file.close();
	return drawing;
}

std::vector<std::string> Game::loadDrawing(const std::string& path) {
	std::vector<std::string> drawing;
	std::ifstream file(path);
	std::string line;
	while (std::getline(file, line)) {
		drawing.push_back(line);
	}
	file.close();
	return drawing;
}