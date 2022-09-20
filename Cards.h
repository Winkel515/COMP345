#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <vector>

enum CardType {
  Bomb,
  Reinforcement,
  Blockade,
  Airlift,
  Diplomacy
}

class Card {
 public:
  Card();

 private:
  Card play();
};

class Deck {
 public:
  Deck();

 private:
  std::vector<Card*> cards;
  Card draw();
  void createDeck();
};

class Hand {
 public:
  Hand();

 private:
  std::vector<Card*> cards;
  std::vector<Card*> fillHand();
};

#endif