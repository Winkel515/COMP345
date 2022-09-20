#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Node {
    public:
      string name;
      vector<Node> adj;
      string continent;
      string color;
      Node(string name, string continent);
};

class Map {
  private:
    vector<Node> territories;
  public:
    Map(vector<Node> territories);
    void printMap();
    void validate();
    void dfs(int currentNode);
};

string convertAdjToString(vector<Node> adj);