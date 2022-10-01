#include <iostream>

#include "Cards.h"

void testCards() {
  std::cout << "Creating deck of cards." << std::endl;
  Deck d1{2};
  d1.showCards();

  Hand player;

  std::cout << "Creating player and drawing 10 cards from deck" << std::endl;
  for (int i = 0; i < 10; i++) {
    player.drawCard(d1);
  }
  d1.showCards();
  player.showCards();

  std::cout << "Playing all cards in player Hand!" << std::endl;

  int sizeOfHand = player.getCards().size();
  for (int i = 0; i < sizeOfHand; i++) {
    player.showCards();
    Card* cardP = player.getCards().at(0);
    cardP->play();
    // remove card from hand and place in deck
    player.swapCardToDeck(d1, 0);
  }

  d1.showCards();
}
int main() { testCards(); }