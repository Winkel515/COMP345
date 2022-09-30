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
  unordered_map<string, vector<Node*>> continentsCopy;
  vector <string> continentsNames;
  vector<Node*> territories;
  vector<Node*> territoriesCopy;
  
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
          territories.push_back(n);
          territoryMap[territoryData[0]] = n;
          
          continentsNames.push_back(territoryData[3]);


          for(int i = 4; i < territoryData.size(); i++) {
            adjTerritories.push_back(territoryData[i]);
          }

          adjMap[territoryData[0]] = adjTerritories;
        }
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

      this->map = new Map(territories);
      //this->map->printMap();
      this->map->validate(continentsNames);
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
  
  cout << "001_I72_Ghtroc 720.map" << endl;
  new MapLoader("001_I72_Ghtroc 720.map");
  cout << endl << endl;

  cout << "002_I72_X-29.map" << endl;
  new MapLoader("002_I72_X-29.map");
  cout << endl << endl;

  cout << "003_I72_Fairchild T-31.map" << endl;
  new MapLoader("003_I72_Fairchild T-31.map");
  cout << endl << endl;

  cout << "004_I72_Cobra.map" << endl;
  new MapLoader("004_I72_Cobra.map");
  cout << endl << endl;

  cout << "005_I72_V-22.map" << endl;
  new MapLoader("005_I72_V-22.map");
  cout << endl << endl;
  /*
  cout << "4D_Hypercube.map" << endl;
  new MapLoader("4D_Hypercube.map");
  cout << endl << endl;
*/
  cout << "99 Mens Morris.map" << endl;
  new MapLoader("99 Mens Morris.map");
  cout << endl << endl;

  cout << "_62_ small - CASTLE MOONBAT.map" << endl;
  new MapLoader("_62_ small - CASTLE MOONBAT.map");
  cout << endl << endl;
/*
  cout << "3D.map" << endl;
  new MapLoader("3D.map");
  cout << endl << endl;

  cout << "3D Cliff.map" << endl;
  new MapLoader("3D Cliff.map");
  cout << endl << endl;
*/
  cout << "_61_ CASTLE MOONBAT.map" << endl;
  new MapLoader("_61_ CASTLE MOONBAT.map");
  cout << endl << endl;



  return 0;
}