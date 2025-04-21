#pragma once
#include <vector>
#include "Character.h"

class Game
{
public:
	static Game* getInstance();

	~Game() {};

	void initialize();
	void run();

public:
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

private:
	Game() = default;

	std::string getHealthBar(const int& healtPoints, const int& remainingHealthPoints);
	void printBattleScene(const int& round);

	void printGameEnd();

private:
	static Game* instance;
	static const int enemiesCount;

	static const std::string grass;
	static std::vector<std::string> mainCharacterDesign;
	static const std::vector<std::vector<std::string>> enemiesDesign;

	static const std::vector<std::string> gameOver;
	static const std::vector<std::string> youWin;

private:
	Character mainCharacter;
	std::vector<Character> enemies;
};

