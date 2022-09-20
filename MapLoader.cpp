#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

MapLoader::MapLoader(string fileName) {
  string myText;
  ifstream MyReadFile(fileName);
  string type;
  unordered_map<string, vector<string>> adjMap;
  unordered_map<string, Node*> territoryMap;
  vector<Node> territories;
  
  
  if (MyReadFile) {
      while (getline (MyReadFile, myText)) {
        //cout << "mytext " << myText;
        if(myText.compare("[Territories]") == 0) {
          type = "[Territories]";
          continue;
        }
        if(type == "[Territories]") {
          vector<string> territoryData = splitString(myText, ",");
          vector<string> adjTerritories;
          Node *n = new Node(territoryData[0], territoryData[3]);
          territories.push_back(*n);
          territoryMap[territoryData[0]] = n;
          for(int i = 4; i < territoryData.size(); i++) {
            adjTerritories.push_back(territoryData[i]);
          }

          adjMap[territoryData[0]] = adjTerritories;
        }
      }

      for(int i = 0; i < territories.size(); i++) {
        vector<string> adj = adjMap[territories[i].name];
        for(int j = 0; j < adj.size(); j++) {
          territories[i].adj.push_back(*territoryMap[adj[j]]);
        }
      }

      this->map = new Map(territories);
  
      this->map->printMap();
      this->map->validate();

  }

  else cout << "Unable to open file" << endl;
  

};

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

int main() {
  new MapLoader("001_I72_Ghtroc 720.map");

  return 0;
}