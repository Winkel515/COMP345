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
      ~Node();
      Node& operator=(const Node& n);
      friend ostream& operator<<(ostream &strm, const Node &n);
};



class Map {
  private:
    vector<Node*> territories; //change Node to Node*
  public:
    Map(vector<Node*> territories); //change Node to Node*
    Map(const Map& m);
    ~Map();
    Map& operator=(const Map& m);
    void printMap();
    void validate(vector <string> continentsNames);
    void dfs(int currentNode, vector<Node*> territoriesCopy);
    void dfs_sub(int currentNode, vector<Node*> continents);
    void setWhite(vector<Node*> territoriesCopy);
    void makeBidirectional(vector<Node*> territories);
    unordered_map<string, vector<Node*>> copyContinents(vector <string> continentsNames, vector<Node*> territoriesCopy);
    friend ostream& operator<<(ostream &strm, const Map &m);
};

string convertAdjToString(vector<Node*> adj);
