#include "Map.h"
#include <vector>
#include <unordered_map>

using namespace std;

Node::Node(string name, string continent) {
  this->name = name;
  this->adj = {};
  this->continent = continent;
  this->color = "WHITE";
  

}

ostream& operator<<(ostream &strm, const Node &n){
  return strm << /*"Node name: " <<*/ n.name;// << "continent: " << n.continent << endl << "color: " << n.color << endl;
}

/*A::A(int _i){
  this->i = _i;
}*/

Map::Map(vector<Node*> territories) { //change Node to Node*
  this->territories = territories;
}

void Map::printMap() {
    
  for(int i = 0; i < territories.size(); i++) {
    cout << "Continent: " << (*territories[i]).continent << " Territory " << (*territories[i]).name << " -> " << convertAdjToString((*territories[i]).adj) << endl;//<< convertAdjToString((*territories[i]).(*adj)) << endl;
    
  }
  
}

void Map::validate(vector <string> continentsNames, unordered_map<string, vector<Node*>> continents) {
  
  for(int i = 0; i < territories.size(); i++){
    if((*territories[i]).color == "WHITE"){
      dfs(i);
    }

  }

  for(int i = 0; i < territories.size(); i++){
    if ((*territories[i]).color != "BLACK") {
      cout << "The map has not the proper format in territories" << endl;
      break;
    }

    if( i == territories.size() - 1 && (*territories[i]).color == "BLACK") {
      cout << "The map has the proper format in territories" << endl;
    }
  }

  bool incorrectMap = false;
  
  for(int i = 0; i < territories.size(); i++){
    for(int j = 0; j < (*territories[i]).adj.size(); j++){
      if ((*(*territories[i]).adj[j]).color != "BLACK") {
        cout << "The map has not the proper format in adj list" << endl;
        incorrectMap = true;
        break;
      }
    }

    if(incorrectMap == true){
      break;
    }

    if(incorrectMap == false && i == territories.size() - 1) {
      cout << "The map has the proper format in adj list" << endl;
    }
  }

  for(int i = 0; i < territories.size(); i++){
    if((*territories[i]).color != "WHITE"){
      (*territories[i]).color = "WHITE";
    }

  }

  for(int i = 0; i < continentsNames.size(); i++){
    for(int j = 0; j < continents[continentsNames[i]].size(); j++){
      if((*continents[continentsNames[i]][j]).color == "WHITE"){
        
        dfs_sub(j, continents[continentsNames[i]]);
      }
    }
  }

  for(int i = 0; i < territories.size(); i++){
    if ((*territories[i]).color != "BLACK") {
      cout << "The sub map has not the proper format" << endl;
      break;
    }

    if( i == territories.size() - 1 && (*territories[i]).color == "BLACK") {
      cout << "The sub map has the proper format" << endl;
    }
  }
  int index = 0;
  
  for(int i = 0; i < territories.size(); i++){
    for(int j = 0; j < continentsNames.size(); j++){
      for(int k = 0; k < continents[continentsNames[j]].size(); k++){
        if((*continents[continentsNames[j]][k]).name == (*territories[i]).name){
          index++;
          
        }
      }
    }
  }
  bool trial = territories.size() == index;
  cout << "index: " << index << " " << trial << endl;
  

}

void Map::dfs(int currentNode){
    (*territories[currentNode]).color = "GRAY";
    /*
    for(int i = 0; i < territories.size(); i++){
      for(int j = 0; j < territories[i].adj.size(); j++){
        if(territories[currentNode].name == territories[i].adj[j].name){
          territories[i].adj[j].color = "GRAY";
        }
        
      }
    }*/

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
    /*
    for(int i = 0; i < territories.size(); i++){
      for(int j = 0; j < territories[i].adj.size(); j++){
        if(territories[currentNode].name == territories[i].adj[j].name){
          territories[i].adj[j].color = "BLACK";
        }
        
      }
    }*/
}

void Map::dfs_sub(int currentNode, vector<Node*> continents){
    (*continents[currentNode]).color = "GRAY";
    
    for(int i = 0; i < (*continents[currentNode]).adj.size(); i++){      
      if((*(*continents[currentNode]).adj[i]).color == "WHITE"){
        for(int j = 0; j < continents.size(); j++){
          if((*continents[j]).name == (*(*continents[currentNode]).adj[i]).name){
            dfs(j);
            break;
          }
        }
      }
    }
  
    (*continents[currentNode]).color = "BLACK";

}

string convertAdjToString(vector<Node*> adj) {
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