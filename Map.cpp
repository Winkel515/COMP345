#include "Map.h"
#include <vector>
#include <unordered_map>

using namespace std;

Node::Node(string name, string continent) { // node constructor, each node represent a territory
  this->name = name;
  this->adj = {};
  this->continent = continent;
  this->color = "WHITE";
  this->belongsToContinent = false;
  

}
/*
Node& Node::operator=(const Node& n){ // overloading assignment operator for node
  this->name = new string((*n.name));
  this->adj = vector<Node*>((*n.adj));
  this->continent = new string(*(n.continent));
  this->color = new string(*(n.continent));
  return *this;
}

Node::Node(const Node& n){ // node copy constructor
  this->name = new string((*n.name));
  this->adj = vector<Node*>((*n.adj));
  this->continent = new string(*(n.continent));
  this->color = new string(*(n.continent));
}*/

ostream& operator<<(ostream &strm, const Node &n){ //overloading stream insertion operator
  return strm << /*"Node name: " <<*/ n.name;// << "continent: " << n.continent << endl << "color: " << n.color << endl;
}

Map::Map(vector<Node*> territories) { // Map constructor
  this->territories = territories;
}

/*
Map& Map::operator=(const Map& m){ // overloading assignment operator for map
  this->territories = vector<Node*>(*(m.territories));
  return *this;
}

Map::Map(const Map& m){ // map copy constructor
  this->territories = vector<Node*>(*(m.territories));
}
*/
void Map::printMap() { // prints the map indicating for each territory the continent, and adjacent territories
    
  for(int i = 0; i < territories.size(); i++) {
    cout << "Continent: " << (*territories[i]).continent << " Territory " << (*territories[i]).name << " -> " << convertAdjToString((*territories[i]).adj) << endl;//<< convertAdjToString((*territories[i]).(*adj)) << endl;
    
  }
  
}

void Map::setWhite(){

  for(int i = 0; i < territories.size(); i++){ //set color of all territory to white
    if((*territories[i]).color != "WHITE"){
      (*territories[i]).color = "WHITE";
    }

  }

}

void Map::validate(vector <string> continentsNames, unordered_map<string, vector<Node*>> continents) { // checks the map and continents are connected graphs and ensures each territory belongs to one and only one continent
  
  bool incorrectMap = false;
  int count = 0;
  for(int i = 0; i < territories.size(); i++){ // runs dfs from each node in territories
    count = 0;
    dfs(i);

    for(int j = 0; j < territories.size(); j++){ //checks if all nodes can be visited from node i
      //cout << (*territories[j]).color << endl;
      if((*territories[j]).color == "BLACK"){
        count += 1;
      }
    }

    if(count == territories.size()){ // if all nodes can be visited from node i all nodes color is set to white to start over with node i + 1
      setWhite();
      continue;
    }
    else{ // otherwise the map does not have the proper format and the loop stops
      cout << "The map is not a connected graph or is a weakly connected graph." << endl;
      incorrectMap = true;
      break;
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
    for(int j = 0; j < continents[continentsNames[i]].size(); j++){
      count = 0;
      dfs_sub(j, continents[continentsNames[i]]);

      for(int k = 0; k < continents[continentsNames[i]].size(); k++){
        //cout << (*continents[continentsNames[i]][k]).color << endl;
        if((*continents[continentsNames[i]][k]).color == "BLACK"){ //checks if all nodes can be visited from j
          count += 1;
        }
      }

      if(count == continents[continentsNames[i]].size()){  // if all nodes can be visited from k it starts over on another continent
        correctContinent = true;
        break;
      }
      else{ // otherwise the loop exits
        correctContinent = false;
        break;
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
  for(int i = 0; i < territories.size(); i++){ // checks that all territories belong to one and only one continent
    for(int j = 0; j < continentsNames.size(); j++){
      for(int k = 0; k < continents[continentsNames[j]].size(); k++){
        if((*continents[continentsNames[j]][k]).name == (*territories[i]).name){
          (*territories[i]).belongsToContinent = true;
          index++;
        }
      }
    }
  }

  bool allBelong = false;

  for(int i = 0; i < territories.size(); i++){ // checks that all territories have a continents
    if((*territories[i]).belongsToContinent != true){
      break;
    }

    if(i == territories.size() - 1 && (*territories[i]).belongsToContinent == true){
      allBelong = true;
    }

  }

  if(territories.size() == index && allBelong){
    cout << "Each territory belongs to one and only one continent." << endl;
  }
  else{
    cout << "Each territory does not belong to one and only one continent." << endl;
  }
}

void Map::dfs(int currentNode){ // dfs algorithm used for the complete map
    (*territories[currentNode]).color = "GRAY";

    for(int i = 0; i < (*territories[currentNode]).adj.size(); i++){      
      if((*(*territories[currentNode]).adj[i]).color == "WHITE"){
        for(int j = 0; j < territories.size(); j++){
          if((*territories[j]).name == (*(*territories[currentNode]).adj[i]).name){
            dfs(j);
            break;
          }
        }
      }
    }
  
    (*territories[currentNode]).color = "BLACK";

}

void Map::dfs_sub(int currentNode, vector<Node*> continents){ // dfs algorithm used for the continents
    (*continents[currentNode]).color = "GRAY";
    
    for(int i = 0; i < (*continents[currentNode]).adj.size(); i++){      
      if((*(*continents[currentNode]).adj[i]).color == "WHITE"){
        for(int j = 0; j < continents.size(); j++){
          if((*continents[j]).name == (*(*continents[currentNode]).adj[i]).name){
            dfs_sub(j, continents);
            break;
          }
        }
      }
    }
  
    (*continents[currentNode]).color = "BLACK";

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