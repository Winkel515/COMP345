#include "Player.h"

// Create players and demonstrate toDefend(), toAttack(), issueOrders() methods.
void testPlayers() {
  cout << "Creating Player 1" << endl;
  Player* p1 = new Player(5, 4);
  cout << *p1;
}