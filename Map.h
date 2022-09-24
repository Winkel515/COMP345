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
      Node(string name, string continent);
      friend ostream& operator<<(ostream &strm, const Node &n);
};



class Map {
  private:
    vector<Node*> territories; //change Node to Node*
  public:
    Map(vector<Node*> territories); //change Node to Node*
    void printMap();
    void validate(vector <string> continentsNames, unordered_map<string, vector<Node*>> continents);
    void dfs(int currentNode);
    void dfs_sub(int currentNode, vector<Node*> continents);
};

string convertAdjToString(vector<Node*> adj);