//industrial
#include "industrial.h"

// constructor
Industry::Industry(vector<vector<Cell>> regions, int worker, int good) {
  region = regions;
  totalWorkers = worker;
  goods = good;
}

Industry::Industry(){};

// MUTATOR AND ACCESSOR FUNCTIONS FOR PRIVATE VARIABLES: region and workers
void Industry::setRegion(vector<vector<Cell>> newRegion) { region = newRegion; }
void Industry::settotalWorkers(int worker) { totalWorkers = worker; }
vector<vector<Cell>> Industry::getRegion() { return region; }
int Industry::gettotalWorkers() { return totalWorkers; }
int Industry::getGoods() {return goods;}

// SIMULATE FUNCTION
// follows rules provided for industrial zone
void Industry::simulate() {
  // for loop to go through each row of the region
  for (int i = 0; i < region.size(); i++) {
    // for loop to go through each cell of row
    for (int j = 0; j < region[i].size(); j++) {
      // create Cell object for current cell
      Cell current = region[i][j];
      int countAdj = 0;     // counter for functions needing 2 adj cells
      int countAdj2 = 0;    // counter for function needing 4 adj cells

      // for loop to go through each adjacent cell
      for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
          // skips over current cell
          if (x == 0 && y == 0) {
            continue;
          }

          // gets index of row and column of adjacent cell
          int row = i + x;
          int column = j + y;

          // checks if row and column indexes are in bound
          if (row >= 0 && row < region.size() && column >= 0 &&
              column < region[i].size()) {
                if(current.type =="I")
                {

               

            // rule 1
            if ((current.population == 0) &&
                (region[row][column].type == "T") && (totalWorkers >= 2)) {
              current.population++;
              current.workers += 2;
              totalWorkers-=2 ;
            }

            // rule 2
            else if ((current.population == 0) &&
                region[row][column].population >= 1 && totalWorkers >= 2) {
              current.population++;
              current.workers += 2;
              totalWorkers -= 2;
            }

            // rule 3
            // updates countAdj if adjacent pop over 1
            if (current.population == 1 &&
                region[row][column].population >= 1 && totalWorkers >= 2) {
              countAdj++;
            }
            // if 2 adjacent cells have pop over 1
            if (countAdj >= 2) {
              current.population++;
              current.workers += 2;
              totalWorkers -=2 ;
              countAdj = 0; // resets counter
            }

            // rule 4
            // updates countAdj2 if adjacent pop over 2
            if (current.population == 2 &&
                region[row][column].population == 2 && totalWorkers >= 2) {
              countAdj2++;
            }
            // if 4 adjacent cells have pop over 2
            if (countAdj2 >= 4) {
              current.population++;
              current.workers += 2;
              totalWorkers -=2;
              countAdj2 = 0; // resets counter
            }
                }

           
          } else {
            break;
          }
        }
      }
      region[i][j] = current;
    }
  }
}

//Pollute function
void Industry::pollute() {
  // stores amount of increased pollution for each adjacent cell
  vector<vector<int>> newPollute(region.size(),
                                 vector<int>(region[0].size(), 0));

  // prints the size of region matrix
  cout << "Region size: " << region.size() << " x " << region[0].size() << endl;

  // for loop for each cell in the region
  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      // creates a cell object for current cell
        Cell current = region[i][j];
        //Cell curr = current.population;
      // print the coordinates and before value of the cell
      //cout << "Before (i=" << i << ", j=" << j << "): " << current.population << endl;

      // checks if the current cell has a pollution value greater than 1
      if (current.population > 1 && current.type == "I") {
        // for loop to go through adjacent cells
        for (int x = -1; x <= 1; x++) {
          for (int y = -1; y <= 1; y++) {
            // skip current cell
            if (x == 0 && y == 0) {
              continue;
            }
            // indexes of adjacent cells
            int row = i + x;
            int col = j + y;

            // prints coordinates of adjacent cell
            //cout << "Adjacent (row=" << row << ", col=" << col << ")" << endl;

            // checks if coordinates are in bounds
            if (row >= 0 && row < region.size() && col >= 0 &&
                col < region[i].size()) {
              // finds distance between adjacent and current cell
              int distance = max(abs(x), abs(y));

              // calculates the increase and make sure it's not negative
              int spread = current.population - distance;
              spread = max(spread, 0);

              // updates vector with amount of increasedpollution
              newPollute[row][col] += spread;
              //cout << "new pollute value "<< newPollute[i][j] << " ";
            }
          }
        }
      }
    }
  }

  // for loop to go through each cell in region and also updates pollution amount
  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      region[i][j].pollution += newPollute[i][j];
    }
  }

  cout << "";
  // prints the matrix at the end
  cout << "Pollution matrix:" << endl;
  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      cout << region[i][j].pollution << " ";
    }
    cout << endl;
  }
}



// GIVEGOODS FUNCTION
// gives goods to commercial zones
void Industry::giveGoods() {
  int totalGoods = 0;
  // for loop to go through each cell in region
  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      Cell current = region[i][j];
      // checks if zone is industrial and has population
      if (current.type == "I" && current.population > 0) {
        totalGoods +=
            current.population; // number of goods = population of cell
      }
    }
  }

  for (int i = 0; i < region.size(); i++) {
    for (int j = 0; j < region[i].size(); j++) {
      Cell current = region[i][j];
      // checks if cell is commercial, hasn't been assigned a good, and
      // has available goods
      if (current.type == "C" && !current.assigned && goods > 0) {
        // assigns goods to cell
        current.goods += 1;
        totalGoods--;
        current.assigned = true;
      }
      region[i][j] = current;
    }
    // breaks if no more goods
    if (totalGoods == 0) {
      break;
    }
  }
  goods= totalGoods;
}
