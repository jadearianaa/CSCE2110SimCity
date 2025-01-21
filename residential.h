#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "city.h"

class Residential 
{
    public:
    Residential();
    void setRegion(vector<vector<Cell>> newRegion);
    vector<vector<Cell>> getRegion();
    void simulate();
    void assignWorkers();
    void setAvailWorkers(int workers);
    int getAvailWorkers();

    private:
    vector<vector<Cell>> regionData;
    Cell cell;
    int workers;
    int availWorkers;


};