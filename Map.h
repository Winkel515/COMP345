#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node {
    public:
      string name;
      vector<Node> adj;
      Node(string name);
};

class Map {
  private:
    vector<Node> territories;
  public:
    Map(vector<Node> territories);
    void printMap();
};

string convertAdjToString(vector<Node> adj);