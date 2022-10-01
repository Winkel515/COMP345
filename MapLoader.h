#include "Map.h"
#include <vector>
#include <string>

using namespace std;

class MapLoader {
  private:
    Map *map;
    string fileName;
  public:
    MapLoader(string fileName);
    ~MapLoader();
    friend ostream& operator<<(ostream &strm, const MapLoader &ml);
};

vector<string> splitString(string s, string delimiter);