#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Player;
using namespace std;

class Node {  // TODO: Change Node to Territory
 public:
  string name;
  vector<Node*> adj;
  string continent;
  string color;
  int numArmies;
  Player* owner;
  void setNumArmies(int _numArmies);
  int getNumArmies();
  void setOwner(Player* _owner);
  Player* getOwner();
  bool belongsToContinent;
  Node(string name, string continent);
  Node(const Node& n);
  Node& operator=(const Node& n);
  friend ostream& operator<<(ostream& strm, const Node& n);
};

class Map {
 private:
  vector<Node*> territories;

 public:
  Map(vector<Node*> territories);
  Map(const Map& m);
  ~Map();
  Map& operator=(const Map& m);
  void printMap();
  void validate(vector<string> continentsNames);
  void dfs(int currentNode, vector<Node*> territoriesCopy);
  void dfs_sub(int currentNode, vector<Node*> continents);
  void setWhite(vector<Node*> territoriesCopy);
  void makeBidirectional(vector<Node*> territories);
  unordered_map<string, vector<Node*>> copyContinents(
      vector<string> continentsNames, vector<Node*> territoriesCopy);
  friend ostream& operator<<(ostream& strm, const Map& m);
};

string convertAdjToString(vector<Node*> adj);
