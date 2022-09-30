#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <vector>

class Card {
 public:
  enum CardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };
  Card(Card::CardType type);
  Card(const Card& other);
  ~Card();
  Card& operator= (const Card& copy);
  friend std::ostream& operator<<(std::ostream& out, const Card& c);

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
  Deck& operator= (const Deck& copy);
  friend std::ostream& operator<<(std::ostream& out, const Deck& d);
  Card* draw();


 private:
  std::vector<Card*> cards;
};

class Hand {
 public:
  ~Hand();
  Hand(const Hand& other);
  Hand& operator=(const Hand& copy);
  friend std::ostream& operator<<(std::ostream& out, const Hand& h);
  std::vector<Card*> drawCard(Deck deck);

 private:
  std::vector<Card*> cards;
};

#endif