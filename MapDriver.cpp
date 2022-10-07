#include "MapDriver.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Map.h"

// free function to test sample files
void testLoadMaps() {
  cout << "001_I72_Ghtroc 720.map" << endl;
  MapLoader("001_I72_Ghtroc 720.map");
  cout << endl << endl;

  cout << "002_I72_X-29.map" << endl;
  MapLoader("002_I72_X-29.map");
  cout << endl << endl;

  cout << "003_I72_Fairchild T-31.map" << endl;
  MapLoader("003_I72_Fairchild T-31.map");
  cout << endl << endl;

  cout << "004_I72_Cobra.map" << endl;
  MapLoader("004_I72_Cobra.map");
  cout << endl << endl;

  cout << "005_I72_V-22.map" << endl;
  MapLoader("005_I72_V-22.map");
  cout << endl << endl;

  cout << "4D_Hypercube.map" << endl;
  MapLoader("4D_Hypercube.map");
  cout << endl << endl;

  cout << "99 Mens Morris.map" << endl;
  MapLoader("99 Mens Morris.map");
  cout << endl << endl;

  cout << "_62_ small - CASTLE MOONBAT.map" << endl;
  MapLoader("_62_ small - CASTLE MOONBAT.map");
  cout << endl << endl;

  cout << "3D.map" << endl;
  MapLoader("3D.map");
  cout << endl << endl;

  cout << "3D Cliff.map" << endl;
  MapLoader("3D Cliff.map");
  cout << endl << endl;

  cout << "_61_ CASTLE MOONBAT.map" << endl;
  MapLoader("_61_ CASTLE MOONBAT.map");
  cout << endl << endl;

  cout << "badFormat.map" << endl;
  MapLoader("badFormat.map");
  cout << endl << endl;

  cout << "notConnected.map" << endl;
  MapLoader("notConnected.map");
  cout << endl << endl;
}