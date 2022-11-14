#include "OrdersDriver.h"

#include <iostream>

#include "Cards.h"
#include "CommandProcessing.h"
#include "GameEngine.h"
#include "Map.h"
#include "Orders.h"
#include "Player.h"

// Test Orders class
void testOrdersList() {
  OrdersList testList;

  /*
  testList.add(new Order(Order::Deploy));
  testList.add(new Order(Order::Advance));
  testList.add(new Order(Order::Bomb));
  testList.add(new Order(Order::Blockade));
  testList.add(new Order(Order::Airlift));
  testList.add(new Order(Order::Negotiate));

  */

  std::cout << testList;

  testList.move(0, 5);

  std::cout << testList;

  testList.remove(2);

  std::cout << testList;

  testList.executeOrders();
}

void testOrderExecution() {
  // create one of each order
  // deploy order
  // A deploy order tells a certain number of army units taken from the
  // reinforcement pool to deploy to a target territory owned by the player
  // issuing this order (1) demonstrate that each order is validated before
  //execution

  Player* p1 = new Player("player 1");
  Player* p2 = new Player("player 2");
  Player* neutral = new Player("Neutral");

  Territory* terr1 = new Territory("player1Territory", "fakeContinent");
  terr1->setOwner(p1);
  p1->addTerritory(terr1);

  Territory* terr2 = new Territory("player2Territory", "fakeContinent");
  terr2->setOwner(p2);
  p2->addTerritory(terr2);

  Territory* terr3 = new Territory("player1Territory2", "fakeContinent");
  terr3->setOwner(p1);
  p1->addTerritory(terr3);

  // make territories adjacent
  terr1->addAdjTerritory(terr2);
  terr1->addAdjTerritory(terr3);

  terr2->addAdjTerritory(terr1);
  terr2->addAdjTerritory(terr3);

  terr3->addAdjTerritory(terr1);
  terr3->addAdjTerritory(terr2);

  terr1->setNumArmies(10);
  terr2->setNumArmies(5);
  terr3->setNumArmies(15);

  // demonstrate that order verifies that territory is owner by player executing
  // the card
  Deploy* p1order1 = new Deploy(terr1, p1, 10);
  std::cout << "Number of armies on terr1 before order 1: " +
                   terr1->getNumArmies()
            << std::endl;
  p1order1->execute();
  std::cout << "Number of armies on terr1 after order 1: " +
                   terr1->getNumArmies()
            << std::endl;

  Deploy* p1order2 = new Deploy(terr2, p1, 10);
  p1order2->execute();  // this should fail because territory belongs to p2

  // test advance order
  /*An advance order tells a certain number of army units to move from a source
territory to a target adjacent territory -> will result in war simulation if
territories are not owned by same people*/

  // show that advance moves armies without war if source and target are owner
  // by same player reset num of armies for terr1-3
  terr1->setNumArmies(10);
  terr2->setNumArmies(5);
  terr3->setNumArmies(15);

  std::cout << "Num of armies in t1 before advance 1: " + terr1->getNumArmies()
            << std::endl;
  std::cout << "Num of armies in t3 before advance 1: " + terr3->getNumArmies()
            << std::endl;

  Advance* p1order3 = new Advance(terr3, terr1, p1, 10);
  p1order3->execute();

  std::cout << "Num of armies in t1 after advance 1: " + terr1->getNumArmies()
            << std::endl;  // should be 0
  std::cout << "Num of armies in t3 after advance 1: " + terr3->getNumArmies()
            << std::endl;  // should be 25

  // show that advance starts war if source and target are not owner by the same
  // player reset territories
  terr1->setNumArmies(10);
  terr2->setNumArmies(5);
  terr3->setNumArmies(15);

  std::cout << "Num of armies in t1 before advance 2: " + terr1->getNumArmies()
            << std::endl;
  std::cout << "Num of armies in t2 before advance 2: " + terr2->getNumArmies()
            << std::endl;

  Advance* p1attackp2 = new Advance(terr2, terr1, p1, 10);
  p1attackp2->execute();

  std::cout << "Num of armies in t1 after advance 2: " + terr1->getNumArmies()
            << std::endl;
  std::cout << "Num of armies in t2 after advance 2: " + terr2->getNumArmies()
            << std::endl;

  // show that advance wont work if territories are not adjacent
  Territory* terr4 = new Territory("Not adjacent Territory", "fake continent");
  terr4->setOwner(p2);
  terr4->setNumArmies(10);

  Advance* p1attackp2attempt2 = new Advance(terr4, terr1, p1, 10);
  p1attackp2attempt2->execute();  // result in error message

  // bomb order test
  // reset num of armies for terr1-3
  terr1->setNumArmies(10);
  terr2->setNumArmies(5);
  terr3->setNumArmies(15);

  std::cout << "p1 -> bomb p1: should result in error" << std::endl;
  Bomb* bomb1 = new Bomb(terr1, p1);
  bomb1->execute();

  // bomb test 2
  std::cout << "Num of armies in t1 before bomb 2: " + terr1->getNumArmies()
            << std::endl;
  std::cout << "Num of armies in t2 before bomb 2: " + terr2->getNumArmies()
            << std::endl;

  Bomb* bomb2 = new Bomb(terr2, p1);
  bomb2->execute();  // should be successful

  std::cout << "Num of armies in t1 after bomb 2: " + terr1->getNumArmies()
            << std::endl;
  std::cout << "Num of armies in t2 after bomb 2: " + terr2->getNumArmies()
            << std::endl;

  // blockade test
  std::cout << "blockade order will transfer territory to neutral player and "
               "double army"
            << std::endl;
  std::cout << "Num of armies in t1 before: " + terr1->getNumArmies()
            << std::endl;
  std::cout << "Owner of t1 before: " << *(terr1->getOwner()) << std::endl;

  std::cout << "Failed blockade order validation: " << std::endl;
  Blockade* block = new Blockade(terr1, p2, neutral);
  block->execute();  // fails because order not owner by p2

  std::cout << "Successful blockade order validation: " << std::endl;
  Blockade* block1 = new Blockade(terr1, p1, neutral);
  block1->execute();

  std::cout << "blockade order will transfer territory to neutral player and "
               "double army"
            << std::endl;
  std::cout << "Num of armies in t1 after: " + terr1->getNumArmies()
            << std::endl;
  //(5) demonstrate that they blockade owner will transfer ownership to the
  //neutral player
  std::cout << "Owner of t1 after: " << *(terr1->getOwner()) << std::endl;

  // airlift
  // reset num of armies for terr1-3
  terr1->setNumArmies(10);
  terr2->setNumArmies(5);
  terr3->setNumArmies(15);

  std::cout
      << "Airlift card will transfer armies from one territory to another:"
      << std::endl;
  std::cout << "Num of armies in t1 before: " + terr1->getNumArmies()
            << std::endl;
  std::cout << "Num of armies in t3 before: " + terr3->getNumArmies()
            << std::endl;

  std::cout << "Unsuccessful airlift order example: " << std::endl;
  Airlift* airlift1 = new Airlift(terr2, terr1, p1, 5);  // error messor
                                                         // expected
  airlift1->execute();

  std::cout << "Successful airlift order example: " << std::endl;
  Airlift* airlift2 = new Airlift(terr3, terr1, p1, 5);
  airlift2->execute();  // success

  std::cout << "Num of armies in t1 after: " + terr1->getNumArmies()
            << std::endl;
  std::cout << "Num of armies in t3 after: " + terr3->getNumArmies()
            << std::endl;

  // negotiate card
  std::cout
      << "Negotiate order will prevent 2 players from attacking each other"
      << std::endl;

  std::cout << "Unsuccessful negotiate order example: " << std::endl;
  std::cout << "Owner of t1: " << *(terr1->getOwner()) << std::endl;
  std::cout << "Owner of t2: " << *(terr2->getOwner()) << std::endl;

  std::cout << "Negotiate target: t1 from p1:" << std::endl;
  Negotiate* nego1 = new Negotiate(terr1, p1);  // error
  nego1->execute();

  std::cout << "Negotiate target: t2 from p1:" << std::endl;
  Negotiate* nego2 = new Negotiate(terr2, p1);
  nego2->execute();

  // try attack order now
  //(4) demonstrate that the negotiate order will prevent attacks between the
  //two players
  std::cout << "attempting attack from p1 on p2:" << std::endl;
  Bomb* bomb3 = new Bomb(terr2, p1);
  bomb3->execute();  // should result in error becuase of ally

  p1->clearDiplomaticAllies();
  p2->clearDiplomaticAllies();

  // demonstrate that ownership is transferred if territory is concquered
  std::cout << "territory 2 owner before: " << *(terr2->getOwner())
            << std::endl;
  std::cout << "attack from p1 on territory 2: " << std::endl;

  // reset num of armies for terr1-3
  terr1->setNumArmies(10);
  terr2->setNumArmies(3);
  terr3->setNumArmies(15);

  std::cout << "Number of armies on terr2: " << terr2->getNumArmies()
            << std::endl;
  std::cout << "Number of armies on terr1: " << terr1->getNumArmies()
            << std::endl;
  // demonstrate that a player will receive a card if he concquered a territory
  // part 1:
  std::cout << "Did player 1 conquer a territory this turn: "
            << p1->getConcqueredFlag() << endl;
  std::cout << "Player 1 attacking with 10 units" << std::endl;
  Advance* advance3 = new Advance(terr2, terr1, p1, 10);
  advance3->execute();

  std::cout << "territory 2 owner after: " << *(terr2->getOwner()) << std::endl;
  std::cout << "attack from p1 on territory 2: " << std::endl;
  std::cout << "Number of armies on terr2 after: " << terr2->getNumArmies()
            << std::endl;
  std::cout << "Number of armies on terr1 after: " << terr1->getNumArmies()
            << std::endl;
  // demonstrate that a player will receive a card if he concquered a territory
  // part 2:
  std::cout << "Did player 1 conquer a territory this turn: "
            << p1->getConcqueredFlag();

  // demonstrate that a the game engine works with order execution
  GameEngine* testEngine = new GameEngine();
  CommandProcessor* cp = testEngine->commandProcessor;

  cp->setNextInput("loadmap 3D.map");
  cp->getCommand();
  testEngine->setState(GameEngineFSA::commandToStateMap.at("loadmap"));
  cp->setNextInput("validatemap");
  cp->getCommand();
  testEngine->setState(GameEngineFSA::commandToStateMap.at("validatemap"));
  cp->setNextInput("addplayer a");
  cp->getCommand();
  cp->setNextInput("addplayer b");
  cp->getCommand();
  testEngine->setState(GameEngineFSA::commandToStateMap.at("addplayer"));
  // issue order command

  testEngine->issueOrdersPhase();

  delete testEngine;

  // receive correct number of units during reinforcements
  // issue only deploy orders if they still have reinforcements
  // issue atttack/defend orders
  // issue card orders
  // removing player from game (no territories)
  // game ends

  delete p1;
  delete p2;
  delete terr1;
  delete terr2;
  delete terr3;
  delete terr4;
  delete neutral;
  delete p1order1;
  delete p1order2;
  delete p1order3;
  delete p1attackp2;
  delete p1attackp2attempt2;
  delete bomb1;
  delete bomb2;
  delete bomb3;
  delete block;
  delete block1;
  delete airlift1;
  delete airlift2;
  delete nego1;
  delete nego2;
  delete advance3;
}