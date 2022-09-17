#include "Map.h"
#include <vector>

using namespace std;

Node::Node(string name) {
  this->name = name;
  this->adj = {};
}

Map::Map(vector<Node> territories) {
  this->territories = territories;
}

void Map::printMap() {
  for(int i = 0; i < territories.size(); i++) {
    cout << territories[i].name << " -> " << convertAdjToString(territories[i].adj) << endl;
  }
}

string convertAdjToString(vector<Node> adj) {
  string s = "[";

  if(adj.size() > 1)
    for(int i = 0; i < adj.size() - 1; i++) {
      s = s + adj[i].name + ", ";
    }
  
  if(adj.size() > 0)
    s = s + adj[adj.size() - 1].name;

  s = s + "]";

  return s;
}