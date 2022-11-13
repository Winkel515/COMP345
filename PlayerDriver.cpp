#include "Map.h"
#include "Player.h"

// Create players and demonstrate toDefend(), toAttack(), issueOrders() methods.
void testPlayers() {
  cout << endl << "Creating Player 1" << endl << endl;
  Player* p1 = new Player(5, 4, 3);

  cout << endl << "----------------------------" << endl;
  cout << endl
       << "Demonstrating Overloaded Stream Insertion Operator for Player"
       << endl;
  cout << *p1;

  cout << endl << "----------------------------" << endl;
  cout << endl << "Demonstrating issueOrder() method for Player 1" << endl;

  // issue arbitrary order
  //(*p1).issueOrder();
  cout << (*p1);

  cout << endl << "----------------------------" << endl;
  cout << endl << "Demonstrating toAttack() method" << endl;
  vector<Territory*> toAttack = (*p1).toAttack();
  for (int i=0; i < toAttack.size(); i++) {
    cout << toAttack.at(i)->getName();
  }

  cout << endl << "----------------------------" << endl;
  cout << endl << "Demonstrating toDefend() method" << endl;
  vector<Territory*> toDefend = (*p1).toDefend();
  for (int i=0; i < toDefend.size(); i++) {
    cout << toDefend.at(i)->getName();
  }
  cout << endl;
}