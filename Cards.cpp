#include "Cards.h"

#include <iostream>
#include <string>
#include <vector>

// Card constructor
Card::Card(Card::CardType type) {
  std::cout << "Card created with default constructor" << std::endl;
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
  TypeOfCard = copy.TypeOfCard;

  return *this;
}

// overloading insertion stream operator for card
std::ostream& operator<<(std::ostream& out, const Card& c) {
  out << c.GetType() << std::endl;
  return out;
}

// overloading insertion stream operator for Card::CardType
std::ostream& operator<<(std::ostream& out, const Card::CardType ct) {
  const std::string cardTypes[] = {"Bomb", "Reinforcement", "Blockade",
                                   "Airlift", "Diplomacy"};
  return out << cardTypes[ct];
}

// destructor class
Card::~Card() {
  std::cout << "Destroyed " << this->GetType() << " Card" << std::endl;
}

// accessor methods
Card::CardType Card::GetType() const { return TypeOfCard; }

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

Deck::Deck(int numOfCardsPerType) {
  for (int i = 0; i < numOfCardsPerType; i++) {
    this->addCardsToDeck();
  }
}

// method to add 1 card of each type to the deck
void Deck::addCardsToDeck() {
  cards.push_back(new Card(Card::Bomb));
  cards.push_back(new Card(Card::Reinforcement));
  cards.push_back(new Card(Card::Blockade));
  cards.push_back(new Card(Card::Airlift));
  cards.push_back(new Card(Card::Diplomacy));
}

// copy constructor
Deck::Deck(const Deck& other) {
  int size = other.cards.size();
  for (int i = 0; i < size; i++) {
    cards.push_back(new Card(other.cards[i]->GetType()));
  }
}

// deck overloading assignment= apperator
Deck& Deck::operator=(const Deck& copy) {
  if (this == &copy) return *this;

  // copy values
  int size = copy.cards.size();
  for (int i = 0; i < size; i++) {
    cards.push_back(new Card(copy.cards[i]->GetType()));
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
Deck::~Deck() { std::cout << "Deck destroyed!" << std::endl; }

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

void Deck::addCard(Card* card) { cards.push_back(card); }

void Deck::showCards() {
  std::cout << "Current cards in deck:\n";
  int size = cards.size();
  for (int i = 0; i < size; i++) {
    std::cout << "Card " << i + 1 << ": " << *cards[i] << std::endl;
  }
}

// hand constructor
Hand::Hand() {}

//  destructor
Hand::~Hand() { std::cout << "Hand Destroyed!" << std::endl; }

// copy constructor
Hand::Hand(const Hand& copy) {
  int size = copy.cards.size();

  for (int i = 0; i < size; i++) {
    cards.push_back(new Card(copy.cards[i]->GetType()));
  }
}
// assignment operator overloading
Hand& Hand::operator=(const Hand& copy) {
  if (this == &copy) return *this;

  // copy values
  int size = copy.cards.size();
  for (int i = 0; i < size; i++) {
    cards.push_back(new Card(copy.cards[i]->GetType()));
  }

  return *this;
}

// overloading insertion operator Hand
std::ostream& operator<<(std::ostream& out, const Hand& h) {
  int size = h.cards.size();

  for (int i = 0; i < size; i++) {
    out << h.cards[i] << "\n";
  }
  out << std::endl;
  return out;
}

// pick a card from a deck at random and add it to the hand, removing it from
// the deck.
void Hand::drawCard(Deck& deck) { cards.push_back(deck.draw()); }

void Hand::showCards() {
  std::cout << "Current cards in hand:\n";
  int size = cards.size();
  for (int i = 0; i < size; i++) {
    std::cout << "Card " << i + 1 << ": " << *cards[i] << std::endl;
  }
}

// play a card from your hand, must specify which deck to put the card back in
// once it is used.
void Hand::playCard(Deck& deck) {
  std::cout << "Choose a card from your deck that you would like to play by "
               "entering the number of the card:"
            << std::endl;
  this->showCards();

  int cardNum;
  std::cin >> cardNum;
  std::cout << "playing card number: " << cardNum << std::endl;
  Card* pickedCard = cards.at(cardNum - 1);
  cards.erase(cards.begin() + cardNum - 1);
  pickedCard->play();
  std::cout << "Placing card back in deck" << std::endl;
  deck.addCard(pickedCard);
}