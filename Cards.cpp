#include "Cards.h"

#include <iostream>
#include <vector>

// Card constructor
Card::Card(Card::CardType type) { TypeOfCard = type; }

// accessor methods
Card::CardType Card::GetType() { return TypeOfCard; }

// mutator methods
void Card::SetType(Card::CardType type) { TypeOfCard = type; }

// each card has a play() method that enables a player to use it during the game
void Card::play() {
  switch (TypeOfCard) {
    case Bomb:
      std::cout << "Special bomb order created\n";
      break;
    case Reinforcement:
      std::cout << "Special Reinforcement order created\n";
      break;
    case Blockade:
      std::cout << "Special Reinforcement order created\n";
      break;
    case Airlift:
      std::cout << "Special Airlift order created\n";
      break;
    case Diplomacy:
      std::cout << "Special Diplomacy order created\n";
      break;
  }
}

// Deck constructor, numOfCards represents the quantity of each type of card,
// there will be an equal amount of each type.

Deck::Deck() { cards = vector<Card*>(); }
Deck::Deck(int numOfCardsPerType) {
  cards = std::vector<Card*>();
  for (int i = 0; i < numOfCardsPerType; i++) {
    cards.push_back(new Card(Card::Bomb));
    cards.push_back(new Card(Card::Reinforcement));
    cards.push_back(new Card(Card::Blockade));
    cards.push_back(new Card(Card::Airlift));
    cards.push_back(new Card(Card::Diplomacy));
  }
}

// draws a random card from the deck
Card* Deck::draw() {
  if (cards.size() < 1) {
    return;
  }
  int random = rand() % cards.size();
  Card* drawnCard = cards.at(random);
  cards.erase(random);
  return drawnCard;
}

// hand constructor
Hand::Hand() { cards = std::vector<Card*>(); }

// pick a card from a deck at random and add it to the hand, removing it from
// the deck.
std::vector<Card*> Hand::drawCard(Deck deck) { cards.push_back(deck.draw()); }