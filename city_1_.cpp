//city
#include "city.h"

City::City() {
  goods = 0;
  workers = 0;
  refreshRate = 0;
  regionFile = "";
  pollutionTotal = 0;
  timeMax = 0;
}

// READCONFIG FUNCTION
// reads in configuration file and stores data
void City ::readConfig(string configFile) {
  ifstream file(configFile);
  string line;

  // checks if file is open
  if (!file.is_open()) {
    cerr << "Error: could not open file." << endl;
    exit(1);
  }

  // get first line: regionFile info
  getline(file, regionFile);
  regionFile.erase(regionFile.begin(), regionFile.begin() + 14);

  // get second line: timeLimit info
  getline(file, line);
  line.erase(line.begin(), line.begin() + 11);
  timeMax = stoi(line);

  // get third line: refreshRate info
  getline(file, line);
  line.erase(line.begin(), line.begin() + 13);
  refreshRate = stoi(line);

  file.close(); // close file
}

// READREGION FUNCTION
// read in region file and store data
void City ::readRegion(string regionFile) {
  ifstream file(regionFile);
  int rowCount = 0;
  string line;

  // checks if file is open
  if (!file.is_open()) {
    cerr << "Error: could not open file." << endl;
    exit(1);
  }

  // while loop to go through each line of data
  while (getline(file, line)) {
    vector<Cell> row; // vector to store data of each row
    stringstream ss(line);
    Cell cell; // Cell type to store info
    string c;

    // while loop to go through each character of the line
    while (getline(ss, c, ',')) {
      cell.type = c;
      cell.population = 0;
      cell.pollution = 0;
      cell.goods = 0;
      cell.workers = 0;
      cell.assigned = false;

      row.push_back(cell); // add cell to row
    }
    region.push_back(row); // add row to region
    rowCount++;
  }

  // checks if file was empty
  if ((rowCount == 0) || (region.empty())) {
    cerr << "Error: empty region file." << endl;
    exit(1);
  }

  file.close(); // close file
}

// PRINTREGION FUNCTION
// prints reigon data
void City::printRegion() {
  // for loop to go through cell of each row
  cout << "Region Layout:" << endl;
  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      // if region is res, ind, com and population of 0, output letter
      // else, output population
      if (region[i][j].type == "R" || region[i][j].type == "I" ||
          region[i][j].type == "C") {
        if (region[i][j].population == 0) {
          cout << region[i][j].type << " ";
        } else {
          cout << region[i][j].population << " ";
        }
      } else {
        cout << region[i][j].type << " ";
      }
    }
    cout << endl;
  }
  cout << endl;
}

// ACCESSOR FUNCTIONS for timeMax, refreshRate, and regionFile
int City::GettimeMax() { return timeMax; }
int City::GetrefreshRate() { return refreshRate; }
string City::GetregionFile() { return regionFile; }
int City::GetPollution() { return pollutionTotal; }
int City::GetGoods() { return goods; }
int City::GetWorkers() { return workers; }

// ANALYZEREGION FUNCTION
// output total, regional population for residential, industrial, and commercial
void City::analyzeRegion() {
  // variables to store total population of each zone
  int resPop = 0;
  int indPop = 0;
  int comPop = 0;

  // for loop to go through each cell of region
  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      // adds population for residential
      if (region[i][j].type == "R") {
        resPop += region[i][j].population;
      }
      // adds population for industrial
      else if (region[i][j].type == "I") {
        indPop += region[i][j].population;
      }
      // adds population for commercial
      else if (region[i][j].type == "C") {
        comPop += region[i][j].population;
      }
    }
  }

  // outputs total population of all zones
  cout << "Population of residential zone: " << resPop << endl;
  cout << "Population of industrial zone: " << indPop << endl;
  cout << "Population of commercial zone: " << comPop << endl;
}

// ANALYZEPOLLUTION FUNCTION
// outputs final pollution state
void City::printPollution() {
  // for loop to go through each cell of region
  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      Cell current = region[i][j];
      // print each cell's pollution
      cout << current.pollution << " ";
    }
    cout << endl;
  }
}

// TOTALPOLLUTION FUNCTION
// finds total pollution in region
void City::totalPollution() {
  // for loop to go through every cell in region
  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      Cell current = region[i][j];
      // adds each cell's pollution to total
      pollutionTotal += current.pollution;
    }
  }
}

// ANALYZECOORD FUNCTION
// analyzes area of user's choice and outputs total population of all zones and
// pollution
void City::analyzeCoord(int x1, int y1, int x2, int y2) {
  // variables for total population of each zone and pollution
  int resPop = 0;
  int indPop = 0;
  int comPop = 0;
  int totalPollution = 0;

  // for loop to go through every cell in region
  for (int i = x1; i <= x2; i++) {
    for (int j = y1; j <= y2; j++) {
      Cell current = region[i][j];
      // finds total pollution
      totalPollution += current.pollution;

      // finds total population for each zone
      // residential population
      if (region[i][j].type == "R") {
        resPop += region[i][j].population;
      }
      // industrial population
      else if (region[i][j].type == "I") {
        indPop += region[i][j].population;
      }
      // commercial population
      else if (region[i][j].type == "C") {
        comPop += region[i][j].population;
      }
    }
  }

  // outputs population of all zones and total pollution
  cout << "Population of residential zone: " << resPop << endl;
  cout << "Population of industrial zone: " << indPop << endl;
  cout << "Population of commercial zone: " << comPop << endl;
  cout << "Total pollution in region: " << totalPollution << endl;
}

// ISVALIDCOORD FUNCTION
// finds if coordinates are in bounds of region
bool City::isvalidCoord(int x, int y) {
  // returns true if coordinates are in bound of region
  return (x >= 0 && x < region.size() && y >= 0 && y < region[0].size());
}

// SIMULATE FUNCTION
// goes through functionalities of each zone
void City::simulate() {
  int timeStep = 1;
  //int nochangecount = 0; // to count how many times hasn't changed
  //int compPop =0; // integers to compare the current population with the time step before
  //int currPop =0;
 // while loop until hasn't changed for 2 consecutive or time limit reached
    while (timeStep < timeMax) //nochangecount < 2
  {
    cout << "Time step: " << timeStep << endl;
    cout << "Available workers: " << workers << endl;
    cout << "Available goods: " << goods << endl;

        //residential
        residential.setRegion(region);
        residential.simulate();
        residential.assignWorkers();

        // industry
        indust.setRegion(residential.getRegion());
        indust.settotalWorkers(residential.getAvailWorkers());
        indust.simulate();
        // the next 3 commented out lines can be used if you only want to find the pollution spread for the final region state (and not over the course of 20 time stamps)
        //if (timeStep >= 19)
        //{
        indust.pollute();
        //}
        indust.giveGoods();
        workers = indust.gettotalWorkers();
        goods = indust.getGoods();
        
        //commercial
        commercial.setRegion(indust.getRegion());
        commercial.setAvailableWorkers(workers);
        commercial.setGoods(goods);
        commercial.simulate();

        workers = commercial.getAvailableWorkers();
        goods = commercial.getGoods();
    // this is commented out because the no change count is wrong and the time step stops early at time step 1
     /*  for (int i = 0; i < region.size(); i++) {
        if (nochangecount == 2) {
          break;
        }
      for (int j = 0; j < region[i].size(); j++) {
          Cell current = indust.getRegion()[i][j];
          Cell comp = region[i][j];


          if (current.population != comp.population ||
          current.goods != comp.goods ||
          current.pollution != comp.pollution) {
          nochangecount = 0;
        } else {
          nochangecount++;
          if (nochangecount == 2) {
            break;
          }
        } */



        // print region at frequency of refresh rate
        if (timeStep % refreshRate == 0) {
          setRegion(commercial.getRegion());
          printRegion();
          cout << endl;
        }
        //region[i][j]= current;
        ++timeStep;
    }

  }
//}
