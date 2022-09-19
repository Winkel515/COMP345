#ifndef CARDS_H
#define CARDS_H
#include <iostream>

class Card {
 public:
  Card();

  Card play();
};

class Bomb : private Card {};

class Reinforcement : private Card {};

class Blockade : private Card {};

class Airlift : private Card {};

class Diplomacy : private Card {};

class Deck {
 private:
  std::list<Card*> cards;

 public:
  Card draw();
};

class Hand {
 private:
  std::list<Card*> cards;

 public:
  std::list<Card*> getCards();
};

#endif