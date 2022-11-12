#include "CardsDriver.h"

#include <iostream>

#include "Cards.h"

// method to test Cards/Hand/Deck classes. Called from MainDriver.
void testCards() {
  std::cout << "Creating deck of cards." << std::endl;
  // creates a deck of cards with 1 cards of each type
  Deck* d1 = new Deck(1);
  // prints out content of card
  d1->showCards();

  // create new hand object using default
  Hand* hand = new Hand();
  //assign deck to hand
  hand->setDeck(d1);

  // draws ten cards from deck. since deck only contains 5 cards, it will
  // automatically create 5 more.
  std::cout << "Creating hand and drawing 10 cards from deck" << std::endl;
  for (int i = 0; i < 10; i++) {
    hand->drawCard();
  }
  // show deck cards and hand cards to prove that swap occured
  d1->showCards();
  hand->showCards();

  std::cout << "Playing all cards in hand Hand!" << std::endl;

  // iterate over hand to call the play method on each card. Should remove the
  // card from hand and place it in deck.
  int sizeOfHand = hand->getCards().size();
  for (int i = 0; i < sizeOfHand; i++) {
    hand->showCards();
    // create basic order object for testing purposes
    //Order* order = new Order();
    //hand->getCards().at(0)->play(d1, order);
    hand->removeCard(0);
    //delete order;
  }

  // proof that cards were returned to deck
  d1->showCards();

  delete d1;
  delete hand;
}