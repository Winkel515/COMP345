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
  unordered_map<string, vector<Node*>> continents;
  vector <string> continentsNames;
  vector<Node*> territories; //change from node to node*
  
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
          territories.push_back(n); //change from *n to n
          territoryMap[territoryData[0]] = n;
          
          continentsNames.push_back(territoryData[3]);
          continents[territoryData[3]].push_back(n);

          for(int i = 4; i < territoryData.size(); i++) {
            adjTerritories.push_back(territoryData[i]);
          }

          adjMap[territoryData[0]] = adjTerritories;
        }
      }

      for(int i = 0; i < territories.size(); i++) {
        vector<string> adj = adjMap[(*territories[i]).name]; //change territories to *territories
        for(int j = 0; j < adj.size(); j++) {
          (*territories[i]).adj.push_back(territoryMap[adj[j]]); //change territories to *territories &*territoryMap to territoryMap
        }
      }

      //remove duplicates continents name
      for(int i = 0; i < continentsNames.size(); i++){
        for(int j = i + 1; j < continentsNames.size(); j++){
           if(continentsNames[i] == continentsNames[j]){
            continentsNames.erase(continentsNames.begin()+j);
            j--;
           }
        }
      }
      //removes territory duplicates in continents list
      for(int i = 0; i < continentsNames.size(); i++){
        for(int j = 0; j < continents[continentsNames[i]].size(); j++){
          for(int k = j + 1; k < continents[continentsNames[i]].size(); k++){
            if(continents[continentsNames[i]][j] == continents[continentsNames[i]][k]){
                continents[continentsNames[i]].erase(continents[continentsNames[i]].begin()+k);
                k--;
            }
          }
        }
      }

      //print updates continents names and associated list
      for(int i = 0; i < continentsNames.size(); i++){
        cout << continentsNames[i] << ": ";
        for(int j = 0; j < continents[continentsNames[i]].size() ; j++){
          cout << " " << *continents[continentsNames[i]][j];
        }
        cout << endl << endl;
      }


      //makes graphs completely birdirectional
      /*for(int i = 0; i < territories.size(); i++){
        for(int j = 0; j < (*territories[i]).adj.size(); j++){
          for(int k = 0; k < territories.size(); k++){
            if((*territories[k]).name == (*(*territories[i]).adj[j]).name){
              for(int l = 0; l < (*territories[k]).adj.size(); l++){
                if((*territories[i]).name == (*(*territories[k]).adj[l]).name){
                  break;
                }

                if( l == ((*territories[k]).adj.size() - 1) && (*territories[i]).name != (*(*territories[k]).adj[l]).name){
                  (*territories[k]).adj.push_back(territories[i]);
                }

              }
            }
          }
        }
      }*/


      

      this->map = new Map(territories);
      this->map->printMap();
      this->map->validate(continentsNames, continents);
      //continentsNames.erase(continentsNames.begin());
      //continentsNames.erase(continentsNames.begin());
      //cout << endl << continentsNames[0] << endl << continentsNames[1] << endl;
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


/*
  int *n1 = new int(17);
  //n1 
  int *n2[1];
  n2[0] = n1;
  cout << "*n1" << endl;
  cout << *n1 << endl;
  cout << "&n1" << endl;
  cout << &n1 << endl;
  cout << "n1" << endl;
  cout << n1 << endl;
  cout << "*n2[0]" << endl;
  cout << *n2[0] << endl;
  cout << "&n2[0]" << endl;
  cout << &n2[0] << endl;
  cout << "n2[0]" << endl;
  cout << n2[0] << endl;
  *n1 = 10;
  
  cout << "*n" << endl;
  cout << *n1 << endl;
  cout << "&n" << endl;
  cout << &n1 << endl;
  cout << "n" << endl;
  cout << n1 << endl;
  cout << "*n2[0]" << endl;
  cout << *n2[0] << endl;
  cout << "&n2[0]" << endl;
  cout << &n2[0] << endl;
  cout << "n2[0]" << endl;
  cout << n2[0] << endl;
  unordered_map<string, Node*> tryMap;
  Node *n;
  n = new Node("name1", "continent1");
  Node *nn;
  nn = new Node("name2", "continent2");
  Node nnn = *n;
  Node *nnnn;
  nnnn = n;
  //A *a = new A(1);
  tryMap["bla"] = n;
  cout << n << endl;
  cout << "bla" << endl;
  cout << nn << endl;
  cout << "nnn" << endl;
  cout << nnn.name << endl;
  (*n).name = "na";
  nnn = *nnnn;
  cout << "nnn" << endl;
  cout << nnn.name << endl;
  Node nnnnn = *tryMap["bla"];
  cout << nnnnn.name << endl;
  
  cout << *n << endl;
  if(*n == *nn){

  }*/
  return 0;
}