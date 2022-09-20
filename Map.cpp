#include "Map.h"
#include <vector>

using namespace std;

Node::Node(string name, string continent) {
  this->name = name;
  this->adj = {};
  this->continent = continent;
  this->color = "WHITE";
}

Map::Map(vector<Node> territories) {
  this->territories = territories;
}

void Map::printMap() {
    
  for(int i = 0; i < territories.size(); i++) {
    cout << "Continent: " << territories[i].continent << " Territory " << territories[i].name << " -> " << convertAdjToString(territories[i].adj) << endl;
    
  }
  
}

void Map::validate() {
  
  for(int i = 0; i < territories.size(); i++){
    if(territories[i].color == "WHITE"){
      dfs(i);
    }

  }

  for(int i = 0; i < territories.size(); i++){
    if (territories[i].color != "BLACK") {
      cout << "The map has not the proper format in territories" << endl;
      break;
    }

    if( i == territories.size() - 1 && territories[i].color == "BLACK") {
      cout << "The map has the proper format in territories" << endl;
    }
  }

  bool incorrectMap = false;
  
  for(int i = 0; i < territories.size(); i++){
    for(int j = 0; j < territories[i].adj.size(); j++){
      if (territories[i].adj[j].color != "BLACK") {
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
}

void Map::dfs(int currentNode){
    territories[currentNode].color = "GRAY";
    
    for(int i = 0; i < territories.size(); i++){
      for(int j = 0; j < territories[i].adj.size(); j++){
        if(territories[currentNode].name == territories[i].adj[j].name){
          territories[i].adj[j].color = "GRAY";
        }
        
      }
    }

    for(int i = 0; i < territories[currentNode].adj.size(); i++){      
      if(territories[currentNode].adj[i].color == "WHITE"){
        for(int j = 0; j < territories.size(); j++){
          if(territories[j].name == territories[currentNode].adj[i].name){
            dfs(j);
            break;
          }
        }
      }
    }

    territories[currentNode].color = "BLACK";
    for(int i = 0; i < territories.size(); i++){
      for(int j = 0; j < territories[i].adj.size(); j++){
        if(territories[currentNode].name == territories[i].adj[j].name){
          territories[i].adj[j].color = "BLACK";
        }
        
      }
    }
}

string convertAdjToString(vector<Node> adj) {
  string s = "[";

  if(adj.size() > 1)
    for(int i = 0; i < adj.size() - 1; i++) {
      s = s + adj[i].name + ", ";
    }
  
  if(adj.size() > 0)
    s = s + adj[adj.size() - 1].name;

  s = s + "]";

  return s;
}