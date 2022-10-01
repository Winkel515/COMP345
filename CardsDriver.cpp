#include <iostream>

#include "Cards.h"

int main() {
  std::cout << "Creating deck of cards." << std::endl;
  Deck d1{2};
  d1.showCards();

  Hand player;

  std::cout << "Creating player and drawing 5 cards from deck" << std::endl;
  for (int i = 0; i < 5; i++) {
    player.drawCard(d1);
  }

  std::cout << "Cards left in deck:" << std::endl;
  d1.showCards();

  std::cout << "Testing play card function." << std::endl;
  player.playCard(d1);

  std::cout << "Player cards remaining: " << std::endl;
  player.showCards();
  std::cout << "Cards remaining in deck: " << std::endl;
  d1.showCards();
}