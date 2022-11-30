#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <string>
#include <vector>

#include "Orders.h"

class Deck;
class Hand;

class Card {
 public:
  enum CardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };
  Card(Card::CardType type);
  Card(const Card& other);
  ~Card();
  Card& operator=(const Card& copy);
  friend std::ostream& operator<<(std::ostream& out, const Card& c);

  void SetType(Card::CardType type);
  Card::CardType GetType() const;
  void play(Deck* deck);

 private:
  Card::CardType TypeOfCard;
};

class Deck {
 public:
  Deck(int numOfCards);
  Deck(const Deck& other);
  ~Deck();
  Deck& operator=(const Deck& copy);
  friend std::ostream& operator<<(std::ostream& out, const Deck& d);
  Card* draw();
  void addCardsToDeck();
  void addCard(Card* card);
  void showCards();
  std::vector<Card*> getCards();

 private:
  std::vector<Card*> cards;
};

class Hand {
 public:
  Hand();
  ~Hand();
  Hand(const Hand& other);
  Hand& operator=(const Hand& copy);
  friend std::ostream& operator<<(std::ostream& out, const Hand& h);
  void drawCard();
  void showCards();
  std::vector<Card*> getCards();
  void removeCard(int indexOfCard);
  Deck* getDeck();
  void setDeck(Deck* deck);
  void setCards(vector<Card*>);

 private:
  std::vector<Card*> cards;
  Deck* deck;
};

#endif