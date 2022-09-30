#include "Cards.h"

#include <iostream>
#include <vector>

// Card constructor
Card::Card(Card::CardType type) { TypeOfCard = type; }

// Copy constructor
Card::Card(const Card& other): TypeOfCard {other.TypeOfCard}{
  std::cout << "Card Copy Constructor Called!" << std::endl;
}

//overloading assignment operator
Card& Card::operator=(const Card& copy){
  if(this == &copy)
    return *this;

  //copy values
  TypeOfCard = copy.TypeOfCard;

  return *this;
}

//overloading insertion stream operator
std::ostream& operator<<(std::ostream& out, const Card& c){
  out << "Card: " << c.TypeOfCard << std::endl;
  return out;
}

//destructor class
Card::~Card(){
    std::cout << "Destroyed Card" << std::endl;
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
    cards.push_back(new Card(Card::Bomb));
    cards.push_back(new Card(Card::Reinforcement));
    cards.push_back(new Card(Card::Blockade));
    cards.push_back(new Card(Card::Airlift));
    cards.push_back(new Card(Card::Diplomacy));
  }
}

//copy constructor
Deck::Deck(const Deck& other){
  int size = other.cards.size();
  for(int i = 0; i < size; i++){
    cards.push_back(new Card(other.cards[i]->GetType()));
  }
}

//deck overloading assignment= apperator
Deck& Deck::operator=(const Deck& copy){
  if(this == &copy)
    return *this;

  //copy values
  int size = copy.cards.size();
  for(int i = 0; i < size; i++){
    cards.push_back(new Card(copy.cards[i]->GetType()));
  }
}

//overloading deck insertion operator
std::ostream& operator<<(std::ostream& out, const Deck& d){
  int size = d.cards.size();
  for(int i = 0; i < size; i++){
    out << d.cards[i] << "\n";
  }
  out << std::endl;
  return out;
}

//deck destructor class 
Deck::~Deck(){
  std::cout << "Deck destroyed!" << std::endl;
}


// draws a random card from the deck
Card* Deck::draw() {
  if (cards.size() < 1) {
    return;
  }
  int random = rand() % cards.size();
  Card* drawnCard = cards.at(random);
  cards.erase(cards.begin() + random);
  return drawnCard;
}

//destructor
Hand::~Hand(){
  std::cout << "Hand Destroyed!" << std::endl;
}

//copy constructor
Hand::Hand(const Hand& copy){
  int size = copy.cards.size();

  for(int i = 0; i < size; i++){
    cards.push_back(new Card(copy.cards[i]->GetType()));
  }
}
//assignment operator overloading
Hand& Hand::operator=(const Hand& copy){
  if(this == &copy)
    return *this;
  
  //copy values
  int size = copy.cards.size();
  for(int i = 0; i < size; i++){
    cards.push_back(new Card(copy.cards[i]->GetType()));
  }
}


//overloading insertion operator Hand
std::ostream& operator<<(std::ostream& out, const Hand& h){
  int size = h.cards.size();

  for(int i = 0; i < size; i++){
    out << h.cards[i] << "\n";
  }
  out << std::endl;
  return out;
}

// pick a card from a deck at random and add it to the hand, removing it from
// the deck.
std::vector<Card*> Hand::drawCard(Deck deck) { cards.push_back(deck.draw()); }