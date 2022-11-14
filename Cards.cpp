#include "Cards.h"

#include <iostream>
#include <string>
#include <vector>

#include "Orders.h"

// Card constructor
Card::Card(Card::CardType type) {
  // std::cout << "Card created with default constructor" << std::endl;
  TypeOfCard = type;
}

// Copy constructor
Card::Card(const Card& other) : TypeOfCard{other.TypeOfCard} {
  std::cout << "Card created with copy constructor" << std::endl;
}

// overloading assignment operator
Card& Card::operator=(const Card& copy) {
  if (this == &copy) return *this;

  // copy values
  TypeOfCard = copy.TypeOfCard;  // shallow copy

  return *this;
}

// overloading insertion stream operator for card
std::ostream& operator<<(std::ostream& out, const Card& c) {
  int type = c.GetType();
  std::string types[] = {"Bomb", "Reinforcement", "Blockade", "Airlift",
                         "Diplomacy"};
  cout << types[type] << std::endl;
  return out;
}

// destructor class
Card::~Card() { std::cout << "Destroyed Card" << std::endl; }

// accessor methods
Card::CardType Card::GetType() const { return TypeOfCard; }

// mutator methods
void Card::SetType(Card::CardType type) { TypeOfCard = type; }

// each card has a play() method that enables a player to use it during the
// game, must give a pointer to a deck to put the card back into after the
// method is called. Must also have a order pointer to set the type of the order
// depending on the card.
void Card::play(Deck* deck) {
  switch (TypeOfCard) {
    case Bomb:
      std::cout << "Bomb card used!\n";
      deck->addCard(this);
      break;
    case Reinforcement:
      std::cout << "Special Reinforcement card used!\n";
      deck->addCard(this);
      break;
    case Blockade:
      std::cout << "Special Blockade card used!\n";
      deck->addCard(this);
      break;
    case Airlift:
      std::cout << "Special Airlift card used!\n";
      deck->addCard(this);
      break;
    case Diplomacy:
      std::cout << "Special Diplomacy card used!\n";
      deck->addCard(this);
      break;
    default:
      std::cout << "Card class error, wrong type" << std::endl;
  }
}

// Deck constructor, numOfCards represents the quantity of each type of card,
// there will be an equal amount of each type.
Deck::Deck(int numOfCardsPerType) {
  for (int i = 0; i < numOfCardsPerType; i++) {
    this->addCardsToDeck();
  }
}

// method to add 1 card of each type to the deck
void Deck::addCardsToDeck() {
  Card* bomb = new Card(Card::Bomb);
  cards.push_back(bomb);

  Card* reinforcement = new Card(Card::Reinforcement);
  cards.push_back(reinforcement);

  Card* blockade = new Card(Card::Blockade);
  cards.push_back(blockade);

  Card* airlift = new Card(Card::Airlift);
  cards.push_back(airlift);

  Card* diplomacy = new Card(Card::Diplomacy);
  cards.push_back(diplomacy);
}

// copy constructor
Deck::Deck(const Deck& other) {
  this->cards = {};
  for (int i = 0; i < other.cards.size(); i++) {
    Card* card = new Card(*(other.cards[i]));
    cards.push_back(card);
  }
}

// deck overloading assignment= apperator
Deck& Deck::operator=(const Deck& copy) {  // TODO: Shallow
  this->cards = {};
  for (int i = 0; i < copy.cards.size(); i++) {
    Card* card = new Card(*(copy.cards[i]));
    cards.push_back(card);
  }
  return *this;
}

// overloading deck insertion operator
std::ostream& operator<<(std::ostream& out, const Deck& d) {
  int size = d.cards.size();
  for (int i = 0; i < size; i++) {
    out << d.cards[i] << "\n";
  }
  out << std::endl;
  return out;
}

// deck destructor class
Deck::~Deck() {
  std::cout << "Destroying deck!" << std::endl;
  for (int i = 0; i < this->cards.size(); i++) {
    delete this->cards[i];
  }
}

// draws a random card from the deck
Card* Deck::draw() {
  if (cards.size() < 1) {
    std::cout << "Deck is empty! Adding cards to deck.." << std::endl;
    this->addCardsToDeck();
  }
  int random = rand() % cards.size();
  Card* drawnCard = cards.at(random);
  cards.erase(cards.begin() + random);
  return drawnCard;
}

// add card*  to the back of a deck object
void Deck::addCard(Card* card) { cards.push_back(card); }

// prints out all of the cards in the deck and their type
void Deck::showCards() {
  std::cout << "Current cards in deck:\n";
  int size = cards.size();
  if (size > 0) {
    for (int i = 0; i < size; i++) {
      std::cout << "Card " << i + 1 << ": " << *cards[i] << std::endl;
    }
  } else {
    std::cout << "No cards left in deck" << std::endl;
  }
}

// getter method for cards
std::vector<Card*> Deck::getCards() { return this->cards; }

// hand constructor
Hand::Hand() {}

// destructor
Hand::~Hand() {
  std::cout << "Hand Destroyed!" << std::endl;
  for (int i = 0; i < this->cards.size(); i++) {
    delete this->cards[i];
  }
}

// copy constructor
Hand::Hand(const Hand& copy) {
  this->cards = {};
  for (int i = 0; i < copy.cards.size(); i++) {
    Card* card = new Card(*(copy.cards[i]));
    cards.push_back(card);
  }
}
// assignment operator overloading
Hand& Hand::operator=(const Hand& copy) {  // TODO: Shallow Copy
  this->cards = {};

  for (int i = 0; i < copy.cards.size(); i++) {
    Card* card = new Card(*(copy.cards[i]));
    cards.push_back(card);
  }

  return *this;
}

// overloading insertion operator Hand
std::ostream& operator<<(std::ostream& out, const Hand& h) {
  int size = h.cards.size();

  for (int i = 0; i < size; i++) {
    out << *h.cards[i] << "\n";
  }
  out << std::endl;
  return out;
}

// pick a card from a deck at random and add it to the hand, removing it from
// the deck.
void Hand::drawCard() {
  Card* card = deck->draw();
  cards.push_back(card);
}

// prints out all the cards in a hand and their type
void Hand::showCards() {
  std::cout << "Current cards in hand:\n";
  int size = cards.size();
  if (size > 0) {
    for (int i = 0; i < size; i++) {
      std::cout << "Card " << i + 1 << ": " << *cards[i] << std::endl;
    }
  } else {
    std::cout << "No cards left in hand" << std::endl;
  }
}

// get cards method
std::vector<Card*> Hand::getCards() { return cards; }

// erases pointer to card from hand, does not delete actual card.
void Hand::removeCard(int indexOfCard) {
  cards.erase(cards.begin() + indexOfCard);
}

Deck* Hand::getDeck() { return deck; }

void Hand::setDeck(Deck* ndeck) { this->deck = ndeck; }