#include "Map.h"
#include "Player.h"

// Create players and demonstrate toDefend(), toAttack(), issueOrders() methods.
void testPlayers() {
  cout << endl << "Creating Player 1" << endl << endl;
  Player* p1 = new Player(5, 4, 3);

  cout << endl << "====================================" << endl;
  cout << endl
       << "Demonstrating Overloaded Stream Insertion Operator for Player"
       << endl;
  cout << *p1;

  cout << endl << "====================================" << endl;
  cout << endl << "Demonstrating issueOrder() method for Player 1" << endl;

  // issue arbitrary order
  (*p1).issueOrder();
  cout << (*p1);

  cout << endl << "====================================" << endl;
  cout << endl << "Demonstrating toAttack() method" << endl;
  list<Node*> toAttack = (*p1).toAttack();
  for (std::list<Node*>::iterator it1 = toAttack.begin(); it1 != toAttack.end();
       ++it1) {
    cout << **it1;
  }

  cout << endl << "====================================" << endl;
  cout << endl << "Demonstrating toDefend() method" << endl;
  list<Node*> toDefend = (*p1).toDefend();
  for (std::list<Node*>::iterator it2 = toDefend.begin(); it2 != toDefend.end();
       ++it2) {
    cout << **it2;
  }
}