#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <string>
#include <vector>

class Card {
 public:
  enum CardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };
  Card(Card::CardType type);
  Card(const Card& other);
  ~Card();
  Card& operator=(const Card& copy);
  friend std::ostream& operator<<(std::ostream& out, const Card& c);
  friend std::ostream& operator<<(std::ostream& out, const Card::CardType c);

  void SetType(Card::CardType type);
  Card::CardType GetType() const;
  void play();

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
  void drawCard(Deck& deck);
  void showCards();
  void playCard(Deck& deck);

 private:
  std::vector<Card*> cards;
};

#endif