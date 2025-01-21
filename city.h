#ifndef CITY_H
#define CITY_H
#include "industrial.h"
#include "residential.h"
#include "commercial.h"
using namespace std;

class City {
public:
  City(); //constructor
  void simulate(); //function to go through rules of zones
  void analyzeRegion(); //output total population for res, ind, com
  void printPollution(); //print pollution of each cell
  void totalPollution(); //print total pollution
  void analyzeCoord(int x1, int y1, int x2, int y2); //analyzes area of user's coordinates
  void readConfig(string configFile); //reads configuration file
  void readRegion(string regionFile); //reads region file
  void printRegion(); //prints region
  int GettimeMax(); //accessor for timeMax
  int GetrefreshRate(); //accessor for refresh rate
  string GetregionFile(); //accessor for region file
  int GetPollution(); //accessor for pollution
  int GetGoods(); //accessor for goods
  int GetWorkers(); //accessor for workers
  bool isvalidCoord(int x, int y); //checks if coordinates are in bounds
  void setRegion(vector<vector<Cell>> newRegion){region = newRegion;}
private:
  vector<vector<Cell>> region; //stores region
  int workers; //number of workers
  int goods ; //number of total goods
  int refreshRate; //refresh rate
  string regionFile; //region file name
  int pollutionTotal; //total pollution
  int timeMax; //max time limit
  Industry indust;
  Residential residential;
  Commercial commercial;
};

#endif
