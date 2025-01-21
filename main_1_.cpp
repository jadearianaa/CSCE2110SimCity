//main
#include "city.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int main() {
  string configFile; //name of configuration file
  string regionFile; //name of region file
  City region = City(); //store region data of type City

  cout << "Enter configuration file: ";
  getline(cin, configFile);

  //read in data of configuration and region files and print region
  region.readConfig(configFile);
  regionFile = region.GetregionFile();
  region.readRegion(regionFile);
  cout << "Initial Region State:" << endl;
  region.printRegion();

  region.simulate();

  cout << "Final Region State:" << endl;
  region.printRegion();

  //output total regoinal population for res, ind, com zones
  region.analyzeRegion();

  //output final pollution state
  region.printPollution();

  //output total pollution in region
  region.totalPollution();
  cout << "Total pollution in region: " << region.GetPollution() << endl;

  //analyze region of area of user's choice
  bool invalid = true;
  int x1, y1, x2, y2;

  //check if coordinates are in bound
  while(invalid){
    cout << "Enter coordinates of rectangular area to analyze (x1 y1 x2 y2): ";
  cin >> x1 >> y1 >> x2 >> y2;
    if (region.isvalidCoord(x1, y1) && region.isvalidCoord(x2, y2)){
      invalid = false;
    }
  }
  region.analyzeCoord(x1, y1, x2, y2);
  return 0;
}
