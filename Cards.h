#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <vector>

class Card {
 public:
  enum CardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };
  Card(Card::CardType type);

  void SetType(Card::CardType type);
  Card::CardType GetType() const;
  void play();

 private:
  Card::CardType TypeOfCard;
};

class Deck {
 public:
  Deck();
  Deck(int numOfCards);

 private:
  std::vector<Card*> cards;
  Card* draw();
};

class Hand {
 public:
  Hand();

 private:
  std::vector<Card*> cards;
  std::vector<Card*> drawCard(int numOfCards, Deck deck);
};

#endif