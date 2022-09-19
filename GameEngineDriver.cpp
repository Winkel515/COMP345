#include <iostream>

#include "GameEngine.h"

// Test the game States
void testGameStates();
int main() { testGameStates(); }

// Implement testGameStates
void testGameStates() {
  std::cout << "Test";
  GameEngine gameEngine;
  gameEngine.run();
}
