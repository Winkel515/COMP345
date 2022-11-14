#pragma once
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
  void addNumArmies(int numArmies);
  int getNumArmies();
  void setOwner(Player* _owner);
  Player* getOwner();
  bool belongsToContinent;
  Territory(string name, string continent);
  Territory(const Territory& n);
  Territory& operator=(const Territory& n);
  friend ostream& operator<<(ostream& strm, const Territory& n);
  string getName();
  string getContinent();
  void addAdjTerritory(Territory* adjTerr); //for testing
};

class Map {
 public:
  vector<Territory*> territories;
  vector<string> continentsNames;
  unordered_map<string, Territory*> nameTerritoryMap;

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
  vector<Territory*> getTerritories();
  vector<string> getContinentsNames();
};

class MapLoader {
 private:
  Map* map;
  string fileName;

 public:
  Map* getMap();
  string loadMap(string fileName);
  MapLoader();
  MapLoader(const MapLoader&);
  ~MapLoader();
  friend ostream& operator<<(ostream& strm, const MapLoader& ml);
};

vector<string> splitString(string s, string delimiter);

string convertAdjToString(vector<Territory*> adj);