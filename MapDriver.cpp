#include "MapDriver.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Map.h"

// free function to test sample files
void testLoadMaps() {
  MapLoader mapLoader = MapLoader();

  cout << "001_I72_Ghtroc 720.map" << endl;
  mapLoader.loadMap("001_I72_Ghtroc 720.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "002_I72_X-29.map" << endl;
  mapLoader.loadMap("002_I72_X-29.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "003_I72_Fairchild T-31.map" << endl;
  mapLoader.loadMap("003_I72_Fairchild T-31.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "004_I72_Cobra.map" << endl;
  mapLoader.loadMap("004_I72_Cobra.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "005_I72_V-22.map" << endl;
  mapLoader.loadMap("005_I72_V-22.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "4D_Hypercube.map" << endl;
  mapLoader.loadMap("4D_Hypercube.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "99 Mens Morris.map" << endl;
  mapLoader.loadMap("99 Mens Morris.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "_62_ small - CASTLE MOONBAT.map" << endl;
  mapLoader.loadMap("_62_ small - CASTLE MOONBAT.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "3D.map" << endl;
  mapLoader.loadMap("3D.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "3D Cliff.map" << endl;
  mapLoader.loadMap("3D Cliff.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "_61_ CASTLE MOONBAT.map" << endl;
  mapLoader.loadMap("_61_ CASTLE MOONBAT.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;

  cout << "badFormat.map" << endl;
  mapLoader.loadMap("badFormat.map");
  cout << endl << endl;

  cout << "notConnected.map" << endl;
  mapLoader.loadMap("notConnected.map");
  mapLoader.getMap()->validate();
  cout << endl << endl;
}