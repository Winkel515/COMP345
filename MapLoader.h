#include "Map.h"
#include <vector>

using namespace std;

class MapLoader {
  Map *map;
  public:
    MapLoader(string fileName);
};

vector<string> splitString(string s, string delimiter);