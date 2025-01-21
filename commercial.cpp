//commercial
#include "city.h"
#include "commercial.h"

//main constructor for commercial
Commercial::Commercial()
{
    good = 0;
    workers = 0;
}
Commercial::Commercial(vector<vector<Cell>>region, int availableWorkers, int goods)
{
    region = region;
    workers = availableWorkers;
    good = goods;
    availableWorkers = 0;
    
}

//mutator and accessor for region
void Commercial::setRegion(vector<vector<Cell>>newRegion )
{
    region = newRegion;
}
vector<vector<Cell>> Commercial::getRegion()
{
    return region;
}


//mutator and accessor for region
void Commercial::setAvailableWorkers(int workers)
{
    availableWorkers = workers;
}

int Commercial::getAvailableWorkers()
{
    return availableWorkers;
}

//mutator and accessor for goods
void Commercial::setGoods(int goods)
{
    good = goods;
}
int Commercial::getGoods()
{
    return good;
}

//simulate function
void Commercial::simulate()
{
    //region rows
    for ( int i = 0; i < region.size(); i++ )
    {
        //row cells
        for ( int j = 0; j < region[i].size(); j++)
        {

            //defines current cell
            Cell current = region[i][j];

            if ( region[i][j].type == "C")
            {
             int cellAdj1 = 0, cellAdj2 = 0;

            //adjacent cells
             for (int x = -1; x<=1; x++)
             {
                 int row = x + i;
                 
                 for (int y = -1; y <= 1; y++)
                 {
                     if ( x==0 && y==0)
                     {
                         continue;
                     }

                     int column = y + j;

                     if (row >= 0 && row < region.size() && column < region[i].size())
                     {
                        if ( current.type == "C")
                        {
                            //rule 1
                            if ((current.population == 0) && (region[row][column].type == "T") && 
                            (availableWorkers >=1) && (good>=1))
                            {
                                current.population++;
                                current.workers +=1;
                                availableWorkers -=1;

                                current.goods += 1;
                                good -=1;
                            }

                            //rule 2
                            else if ((current.population==0) && (region[row][column].population >= 1) && 
                            (workers>=1) && (good >=1))
                            {
                                current.population++;
                                current.workers +=1;
                                availableWorkers -=1;

                                current.goods+=1;
                                good -=1;
                            }

                            //rule 3

                            if ( (current.population == 1) && (region[row][column].population >=1)
                            && (availableWorkers >=1) && (good >=1))
                            {
                                cellAdj2++;
                            }

                            if (cellAdj2 >=2)
                            {
                                current.population++;
                                current.workers +=1;
                                availableWorkers -=1;

                                current.goods +=1;
                                good -=1;

                                cellAdj2 = 0;

                            }


                        }
                     }
                     else
                     {
                         break;
                     }
                 }
             }
             region[i][j] = current;
            }
        }
    }
}
