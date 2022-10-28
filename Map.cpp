#include "Map.h"

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "Cards.h"
#include "MapDriver.h"
#include "Orders.h"
#include "Player.h"

using namespace std;

Territory::Territory(
    string name,
    string continent) {  // node constructor, each node represent a territory
  this->name = name;
  this->adj = {};
  this->continent = continent;
  this->color = "WHITE";
  this->belongsToContinent = false;
  this->owner = NULL;
  this->numArmies = 0;
}

Territory& Territory::operator=(
    const Territory& n) {  // overloading assignment operator for node
  this->name = n.name;
  this->adj = {};
  this->continent = n.continent;
  this->color = n.color;
  this->belongsToContinent = n.belongsToContinent;
  if (n.owner == NULL) {
    this->owner = NULL;
  } else {
    this->owner = new Player(*n.owner);
  }

  this->numArmies = n.numArmies;
  return *this;
}

Territory::Territory(const Territory& n) {  // node copy constructor
  this->name = n.name;
  this->adj = {};
  this->continent = n.continent;
  this->color = n.color;
  this->belongsToContinent = n.belongsToContinent;
  if (n.owner == NULL) {
    this->owner = NULL;
  } else {
    this->owner = new Player(*n.owner);
  }
  this->numArmies = n.numArmies;
}

// setter for owner
void Territory::setOwner(Player* _owner) { this->owner = _owner; }

// getter for owner
Player* Territory::getOwner() { return this->owner; }

// setter for number of armies
void Territory::setNumArmies(int _numArmies) { this->numArmies = _numArmies; }

// getter for number of armies
int Territory::getNumArmies() { return this->numArmies; }

ostream& operator<<(
    ostream& strm,
    const Territory& n) {  // overloading stream insertion operator

  return strm << "continent: " << n.continent << " Territory: " << n.name << " "
              << convertAdjToString(n.adj) << endl;
}

// Map constructor
Map::Map(vector<Territory*> territories, vector<string> continents) {
  this->territories = territories;
  this->continentsNames = continents;
}

Map& Map::operator=(const Map& m) {  // overloading assignment operator for map
  unordered_map<string, Territory*> territoryMap;
  unordered_map<string, vector<string>> adjMap;

  // generating copied nodes
  this->territories = {};
  for (int i = 0; i < m.territories.size(); i++) {
    Territory* copyTerritory = new Territory(*(m.territories[i]));
    territoryMap[copyTerritory->name] = copyTerritory;
    territories.push_back(copyTerritory);
    vector<string> adjTerritories;
    for (int j = 0; j < m.territories[i]->adj.size(); j++) {
      adjTerritories.push_back(m.territories[i]->adj[j]->name);
    }
    adjMap[m.territories[i]->name] = adjTerritories;
  }

  // connecting copied nodes together
  for (int i = 0; i < territories.size(); i++) {
    vector<string> adj = adjMap[territories[i]->name];
    for (int j = 0; j < adj.size(); j++) {
      territories[i]->adj.push_back(territoryMap[adj[i]]);
    }
  }
  return *this;
}

Map::Map(const Map& m) {  // map copy constructor
  unordered_map<string, Territory*> territoryMap;
  unordered_map<string, vector<string>> adjMap;

  // generating copied nodes
  this->territories = {};
  for (int i = 0; i < m.territories.size(); i++) {
    Territory* copyTerritory = new Territory(*(m.territories[i]));
    territoryMap[copyTerritory->name] = copyTerritory;
    territories.push_back(copyTerritory);
    vector<string> adjTerritories;
    for (int j = 0; j < m.territories[i]->adj.size(); j++) {
      adjTerritories.push_back(m.territories[i]->adj[j]->name);
    }
    adjMap[m.territories[i]->name] = adjTerritories;
  }

  // connecting copied nodes together
  for (int i = 0; i < territories.size(); i++) {
    vector<string> adj = adjMap[territories[i]->name];
    for (int j = 0; j < adj.size(); j++) {
      territories[i]->adj.push_back(territoryMap[adj[j]]);
    }
  }

  for (int i = 0; i < m.continentsNames.size(); i++) {
    this->continentsNames.push_back(m.continentsNames.at(i));
  }
}
// map destructor
Map::~Map() {
  for (int i = 0; i < this->territories.size(); i++) {
    delete this->territories[i];
  }
}

// overloading stream insertion operator
ostream& operator<<(ostream& strm, const Map& m) {
  string overloadOuput = "";
  for (int i = 0; i < m.territories.size(); i++) {
    overloadOuput = overloadOuput + m.territories[i]->name + "\n";
  }

  return strm << overloadOuput << endl;
}

// prints the map indicating for each territory the continent, and adjacent
// territories
void Map::printMap() {
  for (int i = 0; i < territories.size(); i++) {
    cout << "Continent: " << (*territories[i]).continent << " Territory "
         << (*territories[i]).name << " -> "
         << convertAdjToString((*territories[i]).adj) << endl;
  }
}

// makes the copy graph bidirectional
void Map::makeBidirectional(vector<Territory*> territoriesCopy) {
  for (int i = 0; i < territoriesCopy.size(); i++) {
    for (int j = 0; j < (*territoriesCopy[i]).adj.size(); j++) {
      for (int k = 0; k < territoriesCopy.size(); k++) {
        if ((*territoriesCopy[k]).name ==
            (*(*territoriesCopy[i]).adj[j]).name) {
          for (int l = 0; l < (*territoriesCopy[k]).adj.size(); l++) {
            if ((*territoriesCopy[i]).name ==
                (*(*territoriesCopy[k]).adj[l]).name) {
              break;
            }

            if (l == ((*territoriesCopy[k]).adj.size() - 1) &&
                (*territoriesCopy[i]).name !=
                    (*(*territoriesCopy[k]).adj[l]).name) {
              (*territoriesCopy[k]).adj.push_back(territoriesCopy[i]);
            }
          }
        }
      }
    }
  }
}

// makes a map of continents
unordered_map<string, vector<Territory*>> Map::copyContinents(
    vector<Territory*> territoriesCopy) {
  unordered_map<string, vector<Territory*>> continentsCopy;

  for (int i = 0; i < continentsNames.size(); i++) {
    continentsCopy[continentsNames[i]] = {};
  }

  for (int i = 0; i < territoriesCopy.size(); i++) {
    continentsCopy[territoriesCopy[i]->continent].push_back(territoriesCopy[i]);
  }

  return continentsCopy;
}

// checks the map and continents are connected graphs and ensures each territory
// belongs to one and only one continent
void Map::validate() {
  Map* copyMap = new Map(*this);
  makeBidirectional(copyMap->territories);
  unordered_map<string, vector<Territory*>> continentsCopy =
      copyContinents(copyMap->territories);
  bool incorrectMap = false;
  int count = 0;

  for (int i = 0; i < copyMap->territories.size();
       i++) {  // runs dfs from each node in territories

    count = 0;
    dfs(i, copyMap->territories);

    for (int j = 0; j < copyMap->territories.size();
         j++) {  // checks if all nodes can be visited from node i
      if (copyMap->territories[j]->color == "BLACK") {
        count += 1;
      }
    }

    if (count == copyMap->territories
                     .size()) {  // if all nodes can be visited from node i it
      break;                     // breaks since the map is weakly connected
    } else if (count != copyMap->territories
                            .size()) {  // otherwise the map does not have the
                                        // proper format and the loop stops
      incorrectMap = true;
      break;
    }
  }

  if (incorrectMap) {
    cout << "The map is not valid." << endl;
  } else {
    cout << "The map valid." << endl;
  }

  bool correctContinent = false;
  for (int i = 0; i < continentsNames.size();
       i++) {  // runs dfs on each node of each continent
    for (int j = 0; j < continentsCopy[continentsNames[i]].size(); j++) {
      count = 0;
      dfs_sub(j, continentsCopy[continentsNames[i]]);

      for (int k = 0; k < continentsCopy[continentsNames[i]].size(); k++) {
        if (continentsCopy[continentsNames[i]][k]->color ==
            "BLACK") {  // checks if all nodes can be visited from j
          count += 1;
        }
      }

      if (count == continentsCopy[continentsNames[i]]
                       .size()) {  // if all nodes can be visited from k it
                                   // starts over on another continent
        correctContinent = true;
        break;
      } else if (count != continentsCopy[continentsNames[i]]
                              .size()) {  // if one continent is wrong it breaks
        correctContinent = false;
        break;
      }
    }
    if (!correctContinent) {
      break;
    }
  }

  if (correctContinent) {
    cout << "Continents have the proper format." << endl;
  } else {
    cout << "Continents do not have the proper format." << endl;
  }

  int index = 0;
  for (int i = 0; i < copyMap->territories.size();
       i++) {  // checks that all territories belong to one and only one
               // continent
    for (int j = 0; j < continentsNames.size(); j++) {
      for (int k = 0; k < continentsCopy[continentsNames[j]].size(); k++) {
        if (continentsCopy[continentsNames[j]][k]->name ==
            copyMap->territories[i]->name) {
          copyMap->territories[i]->belongsToContinent = true;
          index++;
        }
      }
    }
  }

  bool allBelong = false;

  for (int i = 0; i < copyMap->territories.size();
       i++) {  // checks that all territories have a continents
    if (copyMap->territories[i]->belongsToContinent != true) {
      break;
    }

    if (i == copyMap->territories.size() - 1 &&
        copyMap->territories[i]->belongsToContinent == true) {
      allBelong = true;
    }
  }

  if (copyMap->territories.size() == index && allBelong) {
    cout << "Each territory belongs to one and only one continent." << endl;
  } else {
    cout << "Each territory does not belong to one and only one continent."
         << endl;
  }

  delete copyMap;
}

void Map::dfs(int currentTerritory,
              vector<Territory*>
                  territoriesCopy) {  // dfs algorithm used for the complete map

  territoriesCopy[currentTerritory]->color = "GRAY";

  for (int i = 0; i < territoriesCopy[currentTerritory]->adj.size(); i++) {
    if (territoriesCopy[currentTerritory]->adj[i]->color == "WHITE") {
      for (int j = 0; j < territoriesCopy.size(); j++) {
        if (territoriesCopy[j]->name ==
            territoriesCopy[currentTerritory]->adj[i]->name) {
          dfs(j, territoriesCopy);
          break;
        }
      }
    }
  }
  territoriesCopy[currentTerritory]->color = "BLACK";
}

void Map::dfs_sub(int currentTerritory,
                  vector<Territory*> continentsCopy) {  // dfs algorithm used
                                                        // for the continents
  continentsCopy[currentTerritory]->color = "GRAY";

  for (int i = 0; i < continentsCopy[currentTerritory]->adj.size(); i++) {
    if (continentsCopy[currentTerritory]->adj[i]->color == "WHITE") {
      for (int j = 0; j < continentsCopy.size(); j++) {
        if (continentsCopy[j]->name ==
            continentsCopy[currentTerritory]->adj[i]->name) {
          dfs_sub(j, continentsCopy);
          break;
        }
      }
    }
  }
  continentsCopy[currentTerritory]->color = "BLACK";
}

string convertAdjToString(
    vector<Territory*> adj) {  // free function to convert the
                               // adjacency lists to strings
  string s = "[";

  if (adj.size() > 1)
    for (int i = 0; i < adj.size() - 1; i++) {
      s = s + adj[i]->name + ", ";
    }

  if (adj.size() > 0) s = s + adj[adj.size() - 1]->name;

  s = s + "]";

  return s;
}

Map* MapLoader::getMap() { return this->map; }

bool MapLoader::loadMap(string fileName) {
  string myText;
  this->fileName = fileName;
  ifstream MyReadFile(fileName);
  string type;
  unordered_map<string, vector<string>> adjMap;
  unordered_map<string, Territory*> territoryMap;
  unordered_map<string, vector<Territory*>> continentsCopy;
  vector<string> continentsNames;
  vector<Territory*> territories;
  vector<Territory*> territoriesCopy;

  // parse files data
  if (MyReadFile) {
    try {
      bool foundTerritory = false;
      while (getline(MyReadFile, myText)) {
        if (myText.empty()) {
          continue;
        }
        if (myText.compare("[Territories]") == 0) {
          type = "[Territories]";
          foundTerritory = true;
          continue;
        }
        if (type == "[Territories]") {
          vector<string> territoryData = splitString(myText, ",");
          vector<string> adjTerritories;
          Territory* n = new Territory(territoryData[0], territoryData[3]);
          territories.push_back(n);
          territoryMap[territoryData[0]] = n;

          continentsNames.push_back(territoryData[3]);

          for (int i = 4; i < territoryData.size(); i++) {
            adjTerritories.push_back(territoryData[i]);
          }
          adjMap[territoryData[0]] = adjTerritories;
        }
      }

      if (!foundTerritory) {
        throw exception();
      }

      // fills adjacency list of each territory
      for (int i = 0; i < territories.size(); i++) {
        vector<string> adj = adjMap[(*territories[i]).name];
        for (int j = 0; j < adj.size(); j++) {
          (*territories[i]).adj.push_back(territoryMap[adj[j]]);
        }
      }

      // remove duplicates continents name -> change to set if time
      for (int i = 0; i < continentsNames.size(); i++) {
        for (int j = i + 1; j < continentsNames.size(); j++) {
          if (continentsNames[i] == continentsNames[j]) {
            continentsNames.erase(continentsNames.begin() + j);
            j--;
          }
        }
      }

      this->map = new Map(territories, continentsNames);

      return true;
    } catch (const std::exception& e) {
      cout << "The map file does not have a correct format." << endl;
      this->map = NULL;
      return false;
    }
  } else {
    cout << "File does not exist." << endl;
    return false;
  }
};

// overload << operator for MapLoader
ostream& operator<<(
    ostream& strm,
    const MapLoader& ml) {  // overloading stream insertion operator

  return strm << ml.fileName << endl;
}

// MapLoader destructor
MapLoader::~MapLoader() { delete this->map; }

// helper function for parsing
vector<string> splitString(string s, string delimiter) {
  vector<string> split;
  int start = 0;
  for (int i = 0; i < s.size() - delimiter.size();) {
    if (delimiter.compare(s.substr(i, delimiter.size())) == 0) {
      split.push_back(s.substr(start, i - start));
      i = i + delimiter.size();
      start = i;
    } else {
      i++;
    }
  }

  if (start < s.size()) {
    split.push_back(s.substr(start, s.size() - start));
  }

  return split;
}
