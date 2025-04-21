#include <iostream>
#include <fstream>
#include "Game.h"

int main() {
	Game* instance = Game::getInstance();
	instance->initialize();
	instance->run();
	delete instance;
	return 0;
}