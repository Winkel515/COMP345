#include "Map.h"
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

Node::Node(string name, string continent) { // node constructor, each node represent a territory
  this->name = name;
  this->adj = {};
  this->continent = continent;
  this->color = "WHITE";
  this->belongsToContinent = false;
}

Node& Node::operator=(const Node& n){ // overloading assignment operator for node
  this->name = n.name;
  this->adj = {}; //does not copy adjacency list -> populate in copy constructor of map
  this->continent = n.continent;
  this->color = n.color;
  this->belongsToContinent = n.belongsToContinent;
  return *this;
}

Node::Node(const Node& n){ // node copy constructor
  this->name = n.name;
  this->adj = {}; //
  this->continent = n.continent;
  this->color = n.color; //does not copy adjacency list -> populate in copy constructor of map
  this->belongsToContinent = n.belongsToContinent;
}

ostream& operator<<(ostream &strm, const Node &n){ //overloading stream insertion operator
  return strm << /*"Node name: " <<*/ n.name;// << "continent: " << n.continent << endl << "color: " << n.color << endl;
}

Map::Map(vector<Node*> territories) { // Map constructor
  this->territories = territories;
}


Map& Map::operator=(const Map& m){ // overloading assignment operator for map
  unordered_map<string, Node*> territoryMap;
  unordered_map<string, vector<string>> adjMap;

  // generating copied nodes
  this->territories = {};
  for(int i = 0; i < m.territories.size(); i++){
    Node *copyTerritory = new Node(*(m.territories[i]));
    territoryMap[copyTerritory->name] = copyTerritory;
    territories.push_back(copyTerritory);
    vector<string> adjTerritories;
    for(int j = 0; j < m.territories[i]->adj.size(); j++){
      adjTerritories.push_back(m.territories[i]->adj[j]->name);
    }
    adjMap[m.territories[i]->name] = adjTerritories;
  }

  // connecting copied nodes together
  for(int i = 0; i < territories.size(); i++) {
    vector<string> adj = adjMap[territories[i]->name];
    for(int j = 0; j < adj.size(); j++) {
      territories[i]->adj.push_back(territoryMap[adj[i]]);
    }
  }
  return *this;
}

Map::Map(const Map& m){ // map copy constructor
  unordered_map<string, Node*> territoryMap;
  unordered_map<string, vector<string>> adjMap;
  
  // generating copied nodes
  this->territories = {};
  for(int i = 0; i < m.territories.size(); i++){
    Node *copyTerritory = new Node(*(m.territories[i]));
    territoryMap[copyTerritory->name] = copyTerritory;
    territories.push_back(copyTerritory);
    vector<string> adjTerritories;
    for(int j = 0; j < m.territories[i]->adj.size(); j++){
      adjTerritories.push_back(m.territories[i]->adj[j]->name);
    }
    adjMap[m.territories[i]->name] = adjTerritories;
  }

  // connecting copied nodes together
  for(int i = 0; i < territories.size(); i++) {
    vector<string> adj = adjMap[territories[i]->name];
    for(int j = 0; j < adj.size(); j++) {
      territories[i]->adj.push_back(territoryMap[adj[j]]);
    }
  }
}

void Map::printMap() { // prints the map indicating for each territory the continent, and adjacent territories
    
  for(int i = 0; i < territories.size(); i++) {
    cout << "Continent: " << (*territories[i]).continent << " Territory " << (*territories[i]).name << " -> " << convertAdjToString((*territories[i]).adj) << endl;//<< convertAdjToString((*territories[i]).(*adj)) << endl;
    
  }
  
}

void Map::setWhite(vector<Node*> territoriesCopy){
  for(int i = 0; i < territoriesCopy.size(); i++){ //set color of all territory to white
    if(territoriesCopy[i]->color != "WHITE"){
      territoriesCopy[i]->color = "WHITE";
    }
  }
}

void Map::makeBidirectional(vector<Node*> territoriesCopy){
      
      for(int i = 0; i < territoriesCopy.size(); i++){
        for(int j = 0; j < (*territoriesCopy[i]).adj.size(); j++){
          for(int k = 0; k < territoriesCopy.size(); k++){
            if((*territoriesCopy[k]).name == (*(*territoriesCopy[i]).adj[j]).name){
              for(int l = 0; l < (*territoriesCopy[k]).adj.size(); l++){
                if((*territoriesCopy[i]).name == (*(*territoriesCopy[k]).adj[l]).name){
                  break;
                }

                if( l == ((*territoriesCopy[k]).adj.size() - 1) && (*territoriesCopy[i]).name != (*(*territoriesCopy[k]).adj[l]).name){
                  (*territoriesCopy[k]).adj.push_back(territoriesCopy[i]);
                }

              }
            }
          }
        }
      }
}

unordered_map<string, vector<Node*>> Map::copyContinents(vector <string> continentsNames, vector<Node*> territoriesCopy){

  unordered_map<string, vector<Node*>> continentsCopy;

  for(int i = 0; i < continentsNames.size(); i++){
        continentsCopy[continentsNames[i]] = {};
  }

  for(int i = 0; i < territoriesCopy.size(); i++){
        continentsCopy[territoriesCopy[i]->continent].push_back(territoriesCopy[i]);
  }

  return continentsCopy;

}

void Map::validate(vector <string> continentsNames) { // checks the map and continents are connected graphs and ensures each territory belongs to one and only one continent
  Map *copyMap = new Map(*this);
  makeBidirectional(copyMap->territories);
  unordered_map<string, vector<Node*>> continentsCopy = copyContinents(continentsNames, copyMap->territories);

  //delete copyMap;
  //1 do the copy
  //2 make the copy bidirectional
  //cout << (*territories[0]).color << endl;
  
  bool incorrectMap = false;
  int count = 0;
  for(int i = 0; i < copyMap->territories.size(); i++){ // runs dfs from each node in territories
    
    count = 0;
    dfs(i, copyMap->territories);
    
    for(int j = 0; j < copyMap->territories.size(); j++){ //checks if all nodes can be visited from node i
      //cout << (*territories[j]).color << endl;
      if(copyMap->territories[j]->color == "BLACK"){
        count += 1;
      }
    }

    if(count == copyMap->territories.size()){ // if all nodes can be visited from node i all nodes color is set to white to start over with node i + 1
      break;
    }
    else if(count != copyMap->territories.size() && i == copyMap->territories.size() - 1){
      cout << "The map is not a weakly connected graph." << endl;
      incorrectMap = true;
      break;
    }
    else{ // otherwise the map does not have the proper format and the loop stops
      setWhite(copyMap->territories);
      continue;
    }
  }

  if(incorrectMap){
    cout << "The map doens not have a correct format" << endl;
  }
  else{
    cout << "The map has the correct format" << endl;
  }
  
  bool correctContinent = false;
  for(int i = 0; i < continentsNames.size(); i++){ // runs dfs on each node of each continent
    for(int j = 0; j < continentsCopy[continentsNames[i]].size(); j++){
      count = 0;
      dfs_sub(j, continentsCopy[continentsNames[i]]);

      for(int k = 0; k < continentsCopy[continentsNames[i]].size(); k++){
        //cout << (*continents[continentsNames[i]][k]).color << endl;
        if(continentsCopy[continentsNames[i]][k]->color == "BLACK"){ //checks if all nodes can be visited from j
          count += 1;
        }
      }

      if(count == continentsCopy[continentsNames[i]].size()){  // if all nodes can be visited from k it starts over on another continent
        correctContinent = true;
        break;
      }
      else if(count != continentsCopy[continentsNames[i]].size() && j == continentsCopy[continentsNames[i]].size() - 1){
        correctContinent = false;
        break;
      }
      else{ // otherwise the loop exits
        setWhite(continentsCopy[continentsNames[i]]);
        continue;
      }
    }
    if(!correctContinent){
      break;
    }
  }

  if(correctContinent){
    cout << "Continents have the proper format" << endl;
  }
  else{
    cout << "Continents do not have the proper format" << endl;
  }

  
  int index = 0;
  for(int i = 0; i < copyMap->territories.size(); i++){ // checks that all territories belong to one and only one continent
    for(int j = 0; j < continentsNames.size(); j++){
      for(int k = 0; k < continentsCopy[continentsNames[j]].size(); k++){
        if(continentsCopy[continentsNames[j]][k]->name == copyMap->territories[i]->name){
          copyMap->territories[i]->belongsToContinent = true;
          index++;
        }
      }
    }
  }

  bool allBelong = false;

  for(int i = 0; i < copyMap->territories.size(); i++){ // checks that all territories have a continents
    if(copyMap->territories[i]->belongsToContinent != true){
      break;
    }

    if(i == copyMap->territories.size() - 1 && copyMap->territories[i]->belongsToContinent == true){
      allBelong = true;
    }

  }

  if(copyMap->territories.size() == index && allBelong){
    cout << "Each territory belongs to one and only one continent." << endl;
  }
  else{
    cout << "Each territory does not belong to one and only one continent." << endl;
  }
  //delete copyMap;
}

void Map::dfs(int currentNode, vector<Node*> territoriesCopy){ // dfs algorithm used for the complete map
  
    territoriesCopy[currentNode]->color = "GRAY";
    
    for(int i = 0; i < territoriesCopy[currentNode]->adj.size(); i++){      
      if(territoriesCopy[currentNode]->adj[i]->color == "WHITE"){
        for(int j = 0; j < territoriesCopy.size(); j++){
          if(territoriesCopy[j]->name == territoriesCopy[currentNode]->adj[i]->name){
            //cout << "bla" << endl;
            dfs(j, territoriesCopy);
            
            break;
          }
        }
      }
    }
    
    territoriesCopy[currentNode]->color = "BLACK";


}

void Map::dfs_sub(int currentNode, vector<Node*> continentsCopy){ // dfs algorithm used for the continents
    continentsCopy[currentNode]->color = "GRAY";
    
    for(int i = 0; i < continentsCopy[currentNode]->adj.size(); i++){      
      if(continentsCopy[currentNode]->adj[i]->color == "WHITE"){
        for(int j = 0; j < continentsCopy.size(); j++){
          if(continentsCopy[j]->name == continentsCopy[currentNode]->adj[i]->name){
            dfs_sub(j, continentsCopy);
            break;
          }
        }
      }
    }
  
    continentsCopy[currentNode]->color = "BLACK";

}

string convertAdjToString(vector<Node*> adj) { // free function to convert the adjacency lists to strings
  string s = "[";

  if(adj.size() > 1)
    for(int i = 0; i < adj.size() - 1; i++) {
      s = s + adj[i]->name + ", ";
    }
  
  if(adj.size() > 0)
    s = s + adj[adj.size() - 1]->name;

  s = s + "]";

  return s;
}