#include "Cards.h"

#include <iostream>
#include <string>
#include <vector>

#include "Orders.h"

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

// each card has a play() method that enables a player to use it during the
// game, must give a reference to a deck to put the card back into after the
// method is called
Order* Card::play(Deck& deck) {
  Order* order{};
  switch (TypeOfCard) {
    case Bomb:
      std::cout << "Special bomb order created\n";
      // create card order
      order = new Order(Order::Bomb);  // allocated on the heap
      // place card back in the deck
      deck.addCard(this);
      return order;
      break;
    case Reinforcement:
      std::cout << "Special Reinforcement order created\n";
      order = new Order(Order::Deploy);
      deck.addCard(this);
      return order;
      break;
    case Blockade:
      std::cout << "Special Blockade order created\n";
      order = new Order(Order::Blockade);
      deck.addCard(this);
      return order;
      break;
    case Airlift:
      std::cout << "Special Airlift order created\n";
      order = new Order(Order::Airlift);
      deck.addCard(this);
      return order;
      break;
    case Diplomacy:
      std::cout << "Special Diplomacy order created\n";
      order = new Order(Order::Negotiate);
      deck.addCard(this);
      return order;
      break;
    default:
      std::cout << "Card class error, wrong type" << std::endl;
      return order;
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
Deck& Deck::operator=(const Deck& copy) {  // TODO: Shallow
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
Deck::~Deck() {
  std::cout << "Destroying deck!" << std::endl;
  for (Card* obj : cards) {
    delete obj;
    obj = nullptr;
  }
  cards.clear();
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

void Deck::addCard(Card* card) { cards.push_back(card); }

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

//  destructor
Hand::~Hand() {
  std::cout << "Hand Destroyed!" << std::endl;
  for (Card* obj : cards) delete obj;
  cards.clear();
}

// copy constructor
Hand::Hand(const Hand& copy) {
  int size = copy.cards.size();

  for (int i = 0; i < size; i++) {
    cards.push_back(new Card(copy.cards[i]->GetType()));
  }
}
// assignment operator overloading
Hand& Hand::operator=(const Hand& copy) {  // TODO: Shallow Copy
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

void Hand::swapCardToDeck(Deck& deck, int indexOfCard) {
  Card* cardP = cards.at(indexOfCard);
  cards.erase(cards.begin() + indexOfCard);
  deck.addCard(cardP);
}
