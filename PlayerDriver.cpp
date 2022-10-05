#include "Player.h"

// Create players and demonstrate toDefend(), toAttack(), issueOrders() methods.
void testPlayers() {
  cout << endl << "Creating Player 1" << endl << endl;
  Player* p1 = new Player(5, 4, 3);
  cout << *p1;
}