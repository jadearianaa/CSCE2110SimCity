#ifndef INDUSTRY_H
#define INDUSTRY_H
#include "cell.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Industry {
public: 
  Industry();
  Industry(vector<vector<Cell>> regions, int worker, int good); //constructor
  void simulate(); //simulates rules of industrial zone
  void giveGoods(); //gives goods to commercial zones
  void pollute(); //pollutes adjacent cells
  void setRegion(vector<vector<Cell>> newRegion); //mutator for region
  void settotalWorkers(int worker); //mutator for workers
  vector<vector<Cell>> getRegion(); //accessor for region
  int gettotalWorkers(); //accessor for workers
  int getGoods(); //accessor for goods

private: 
  vector<vector<Cell>> region; //variable for region
  Cell cell; //cell object
  int totalWorkers; //number of workers
  int goods;
};
#endif
