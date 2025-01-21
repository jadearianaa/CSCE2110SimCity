#include "city.h"

using namespace std;

    //mutator and accessor functions for the region
    void Residential::setRegion(vector<vector<Cell>> newRegion){regionData = newRegion;}
    vector<vector<Cell>> Residential::getRegion() {return regionData;}
    void Residential::setAvailWorkers(int workers) {availWorkers = workers;}
    int Residential::getAvailWorkers() {return availWorkers;}
    
    Residential::Residential() // sets workers and avaiable workers to zero as soon as a residential object is declared
    {
        workers = 0;
        availWorkers = 0;
    }
    //function that follows the statements provided for the residential zone
    void Residential::simulate()
    {   
        //loop that goes through the whole region
        for(int i = 0; i < regionData.size(); i++)
        {  
            for(int j = 0; j < regionData[i].size(); j++)
            {
                //creating a cell object for the current cell
                Cell current = regionData[i][j]; 
                if(regionData[i][j].type == "R") //making sure this only applies to residential
                {
                    int cellAdj1 = 0; //adjacent and population of 1+ 
                    int cellAdj2 = 0; //adjacent and population of 2+
                    int cellAdj3 = 0; //adjacent and population of 3+
                    int cellAdj4 = 0; //adjacent and population of 4+
                      for (int x = -1; x <= 1; x++)
                       {        //gets index row of adjacent cell
                                int row = i + x;
                            for (int y = -1; y <= 1; y++) 
                            { // skips over current cell
                                if (x == 0 && y == 0) 
                                {continue; }
                                // gets index column of adjacent cell
                                int column = j + y;

                                // checks if row and column indexes are in bound
                                    if (row >= 0 && row < regionData.size() && column >= 0 &&column < regionData[i].size()) 
                                        {
                                            //rule 1
                                            if((current.population ==  0)  && (regionData[row][column].type == "T")) 
                                            {
                                                ++current.population;
                                                break;
                                
                                            }
                                            
                                            //rule 2
                                            else if((current.population == 0) && (regionData[row][column].population >= 1))
                                            {
                                                ++current.population;
                                                break;
                                
                                            
                                            }

                                            //adding amount of adjacent cells based off of population before the rules
                                            if((current.population == 1) && regionData[row][column].population >= 1)
                                            {++cellAdj1;} // adding up the adjacent cells with population 1+
                                            
                                            if((current.population == 2) && regionData[row][column].population >= 2)
                                            {++cellAdj2;} // adding up the adjacent cells with population 2+

                                            if((current.population == 3) && regionData[row][column].population >= 3)
                                            {++cellAdj3;} // adding up the adjacent cells with population 3+

                                            if((current.population == 4) && regionData[row][column].population >= 4)
                                            {++cellAdj4;} // adding up the adjacent cells with population 4+

                                            //rule 3
                                            else if((current.population == 1) && (cellAdj1 >= 2))
                                            {
                                                ++current.population;
                                                break;
                                
                                            }

                                            //rule 4
                                            else if((current.population == 2) && (cellAdj2 >= 4))
                                            {
                                                ++current.population;
                                                break;
                                
                                            }

                                            //rule 5
                                            else if((current.population == 3) && (cellAdj3 >= 6))
                                            {
                                                ++current.population;
                                                break;
                                
                                            }
                                                //rule 6
                                            else if((current.population == 4) && (cellAdj4 >= 8))
                                            {
                                                ++current.population;
                                                break;
                                            }
                                            
                                        }
                                        regionData[i][j] = current;

                            }  

                        } // resetting counters
                        cellAdj1 =0;
                        cellAdj2 =0;
                        cellAdj3 =0;
                        cellAdj4 =0;
                } 
            }  
        }  

        for (int i = 0; i < regionData.size(); i++) 
        {
            for (int j = 0; j < regionData[i].size(); j++) 
            {
            // adds population for residential
                if (regionData[i][j].type == "R") 
                {
                workers += regionData[i][j].population;
                }
            }
        setAvailWorkers(workers);// make all the residential population avaiable
        workers = 0; //reset the worker count;

        }
    }
    void Residential::assignWorkers() // may be uneccessary as other functions assign workers themselves
    {
        
        for (int i = 0; i < regionData.size(); i++) 
        {
            for (int j = 0; j < regionData[i].size(); j++) 
            {

                            // checks if cell is commercial, if its been assigned a worker, and that there are available workers
                            if ((regionData[i][j].type == "C") && (regionData[i][j].assigned) && (availWorkers > 0)) 
                            {
                            // removes assigned workers from count
                           availWorkers -= regionData[i][j].workers;
                            }
                            else if ((regionData[i][j].type == "I") && (regionData[i][j].assigned) && (availWorkers > 0)) // checks if cell is industrial, has been assigned a worker, and that there are available workers
                            {
                            // removes assigned workers from count
                           availWorkers -= regionData[i][j].workers ;
                            }
                       // } 
                            // ends if no more avaiable workers
                        if (availWorkers == 0) {break;}
          
                    // }
            }
        }
     }
