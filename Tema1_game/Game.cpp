#include "Game.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

Game* Game::instance = nullptr;
const int Game::enemiesCount = 15;

const std::string Game::grass = "^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~";

std::vector<std::string> Game::mainCharacterDesign = {
	"  .----. ",
	" _|____|_",
	" (  . . )",
	"  |__^_| ",
	"   / V\\ ",
	"  /____\\",
	"    b b  "
};

const std::vector<std::vector<std::string>> Game::enemiesDesign = {
	{
		"  /\\                 /\\  ",
		" / \\'._   (\\_/)   _.'/ \\ ",
		"/_.''._'--('.')--'_.''._\\",
		"| \\_ / `;=/ \" \\=;` \\ _/ |",
		" \\/ `\\__|`\\___/`|__/` \\/",
		"  `       \\(/|\\)/       `",
		"          \"   \"          "
	},

	{
		" /\\                 /\\ ",
		"/ \\'._   (\\_/)   _.'/ \\",
		"|.''._'--(O.O)--'_.''.|",
		" \\_ / `;=/ \" \\=;` \\ _/ ",
		"   `\\__| \\___/ |__/`  ",
		"        \\(_|_)/       ",
		"         \"   \"         "
	},

	{
		"    =/\\                 /\\=     ",
		"    / \\'._   (\\_/)   _.'/ \\     ",
		"   / .''._'--(o.o)--'_.''. \\    ",
		"  /.` _/ |`'=/ \" \\='`| \\_ `.\\   ",
		" /  .' `\\;-,'\\___/',-;/` '.  \\ ",
		"/.-`        \\(_|_)/        `-.\\",
		"             \"   \"              "
	}
};

const std::vector<std::string> Game::gameOver = {
	"  ___                                         ",
	" / __| __ _  _ __   ___     ___ __ __ ___  _ _ ",
	"| (_ |/ _` || '  \\ / -_)   / _ \\\\ V // -_)| '_|",
	"  \\___|\\__/_||_|_|_|\\___|   \\___/ \\_/ \\___||_|  "
};

const std::vector<std::string> Game::youWin = {
	" _ _                     _      ",
	"| | | ___  _ _    _ _ _ [_] _ _ ",
	"\\   // . \\| | |  | | | || || ' |",
	"  |_| \\___/ \\__|  |__/_/ |_||_|_|"
};

Game* Game::getInstance() {
	if (instance == nullptr)
		instance = new Game();
	return instance;
}

void Game::initialize() {
	std::ifstream file("file.in");
	file >> mainCharacter;
	for (int i = 0; i < enemiesCount; i++) {
		Character currentEnemy;
		file >> currentEnemy;
		enemies.push_back(currentEnemy);
	}
	file.close();
}

void Game::run() {
	std::sort(enemies.begin(), enemies.end());
	int index = 0, option;
	while (index < enemiesCount && mainCharacter.isAlive()) {
		printBattleScene(index);
		std::cin >> option;
		if (option == 1) {
			mainCharacter.attack(enemies[index]);
		}
		else if (option == 2) {
			if (mainCharacter.getHealthPotionsCount() > 0)
				mainCharacter.heal();
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
		if (!enemies[index].isAlive()) {
			index++;
			if (index != 0 && index % 2 == 0)
				mainCharacter++;
		}
		else
			enemies[index].attack(mainCharacter);
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
	std::cout << std::setw(30) << (mainCharacter.getName() + " (Lvl " + std::to_string(mainCharacter.getLvl()) + ")") << std::endl;
	std::cout << std::setw(30) << ("Attack: " + std::to_string(mainCharacter.getAttackDamage()) + " | Defence: " + std::to_string(mainCharacter.getDefence())) << std::endl;
	std::cout << std::setw(30) << ("Healing potions: " + std::to_string(mainCharacter.getHealthPotionsCount())) << std::endl;
	std::cout << std::setw(26) << ("HP: " + std::to_string(mainCharacter.getRemainingHealthPoints()) + "/" + std::to_string(mainCharacter.getHealthPoints()));
	std ::cout << std::right << std::setw(20) << "HP: " << enemies[round].getRemainingHealthPoints() << "/" << enemies[round].getHealthPoints() << std::endl;
	std::cout << std::left << std::setw(26) << getHealthBar(mainCharacter.getHealthPoints(), mainCharacter.getRemainingHealthPoints());
	std::cout << std::right << std::setw(26) << getHealthBar(enemies[round].getHealthPoints(), enemies[round].getRemainingHealthPoints()) << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < mainCharacterDesign.size(); i++) {
		std::cout << mainCharacterDesign[i];
		std::cout << std::right << std::setw(45) << enemiesDesign[round % 3][i];
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
	if (!mainCharacter.isAlive()) {
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
		std::cout << "Your final statul is: " << std::endl << mainCharacter;
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
		std::cout << "Your final statul is: " << std::endl << mainCharacter;
	}
}
