#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Player;
using namespace std;

class Territory {
 public:
  string name;
  vector<Territory*> adj;
  string continent;
  string color;
  int numArmies;
  Player* owner;
  void setNumArmies(int _numArmies);
  int getNumArmies();
  void setOwner(Player* _owner);
  Player* getOwner();
  bool belongsToContinent;
  Territory(string name, string continent);
  Territory(const Territory& n);
  Territory& operator=(const Territory& n);
  friend ostream& operator<<(ostream& strm, const Territory& n);
};

class Map {
 private:
  vector<Territory*> territories;
  vector<string> continentsNames;

 public:
  Map(vector<Territory*> territories, vector<string> continentsNames);
  Map(const Map& m);
  ~Map();
  Map& operator=(const Map& m);
  void printMap();
  bool validate();
  void dfs(int currentTerritory, vector<Territory*> territoriesCopy);
  void dfs_sub(int currentTerritory, vector<Territory*> continents);
  void makeBidirectional(vector<Territory*> territories);
  unordered_map<string, vector<Territory*>> copyContinents(
      vector<Territory*> territoriesCopy);
  friend ostream& operator<<(ostream& strm, const Map& m);
  void distributeTerritories(vector<Player*> players);
};

class MapLoader {
 private:
  Map* map;
  string fileName;

 public:
  Map* getMap();
  bool loadMap(string fileName);
  ~MapLoader();
  friend ostream& operator<<(ostream& strm, const MapLoader& ml);
};

vector<string> splitString(string s, string delimiter);

string convertAdjToString(vector<Territory*> adj);