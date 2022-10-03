#include "MapDriver.h"
#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>


using namespace std;

MapLoader::MapLoader(string fileName) {
  string myText;
  this->fileName = fileName;
  ifstream MyReadFile(fileName);
  string type;
  unordered_map<string, vector<string>> adjMap;
  unordered_map<string, Node*> territoryMap;
  unordered_map<string, vector<Node*>> continentsCopy;
  vector <string> continentsNames;
  vector<Node*> territories;
  vector<Node*> territoriesCopy;

  //parse files data
  if (MyReadFile) {
    try
    {
      bool foundTerritory = false;
      while (getline (MyReadFile, myText)) {
        if(myText.empty()){
          continue;
        }
        if(myText.compare("[Territories]") == 0) {
          type = "[Territories]";
          foundTerritory = true;
          continue;
        }
        if(type == "[Territories]") {
          vector<string> territoryData = splitString(myText, ",");
          vector<string> adjTerritories;
          Node *n = new Node(territoryData[0], territoryData[3]);
          territories.push_back(n);
          territoryMap[territoryData[0]] = n;
          
          continentsNames.push_back(territoryData[3]);

          for(int i = 4; i < territoryData.size(); i++) {
            adjTerritories.push_back(territoryData[i]);
          }
          adjMap[territoryData[0]] = adjTerritories;
        }
      }
        
      if(!foundTerritory){
        throw exception();
      }

      //fills adjacency list of each territory
      for(int i = 0; i < territories.size(); i++) {
        vector<string> adj = adjMap[(*territories[i]).name]; 
        for(int j = 0; j < adj.size(); j++) {
          (*territories[i]).adj.push_back(territoryMap[adj[j]]);
        }
      }

      //remove duplicates continents name -> change to set if time
      for(int i = 0; i < continentsNames.size(); i++){
        for(int j = i + 1; j < continentsNames.size(); j++){
           if(continentsNames[i] == continentsNames[j]){
            continentsNames.erase(continentsNames.begin()+j);
            j--;
           }
        }
      }

      //creates and validates created map
      this->map = new Map(territories);
      this->map->validate(continentsNames);
    }
    catch(const std::exception& e)
    {
      cout << "The map does not have a correct format" << endl;
      this->map = NULL;
    }
  }
  else cout << "Unable to open file" << endl;
};

//overload << operator for MapLoader
ostream& operator<<(ostream &strm, const MapLoader &ml){ //overloading stream insertion operator
  
  return strm << ml.fileName << endl;
}

//MapLoader destructor
MapLoader::~MapLoader(){
  delete this->map;
}

//helper function for parsing
vector<string> splitString(string s, string delimiter) {
  vector<string> split;
  int start = 0;
  for(int i = 0; i < s.size() - delimiter.size();) {
    if(delimiter.compare(s.substr(i,delimiter.size())) == 0) {
      split.push_back(s.substr(start, i-start));
      i = i + delimiter.size();
      start = i;
    } else {
      i++;
    }
  }

  if(start < s.size()) {
    split.push_back(s.substr(start, s.size()-start));
  }

  return split;
}

