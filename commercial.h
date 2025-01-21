#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include "city.h"

class Commercial
{
    public:
    Commercial();
    Commercial(vector<vector<Cell>> regionData, int workers, int goods);

    //mutator and accessor for region
    void setRegion(vector<vector<Cell>> regionData);
    vector<vector<Cell>> getRegion();

    //mutator and accessor for workers
    void setAvailableWorkers(int workers);
    int getAvailableWorkers();

    //mutator and accessor for goods
    void setGoods(int goods);
    int getGoods();

    void simulate();
    void assignWorkers();

    private:
    Cell cell;
    vector<vector<Cell>> region;
    int workers;
    int availableWorkers;
    int good;

};

#endif
