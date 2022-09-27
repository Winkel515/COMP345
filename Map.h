#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;


class Node {
    public:
      string name;
      vector<Node*> adj; //need to be pointer to nodes -> Node to Node*
      string continent;
      string color;
      bool belongsToContinent;
      Node(string name, string continent);
      Node(const Node& n);
      Node& operator=(const Node& n);
      friend ostream& operator<<(ostream &strm, const Node &n);
};



class Map {
  private:
    vector<Node*> territories; //change Node to Node*
  public:
    Map(vector<Node*> territories); //change Node to Node*
    Map(const Map& m);
    Map& operator=(const Map& m);
    void printMap();
    void validate(vector <string> continentsNames, unordered_map<string, vector<Node*>> continents);
    void dfs(int currentNode);
    void dfs_sub(int currentNode, vector<Node*> continents);
    void setWhite();
};

string convertAdjToString(vector<Node*> adj);
