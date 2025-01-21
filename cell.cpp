#include <string>
using namespace std;
struct Cell {
  string type;
  int population;
  int pollution;
  int goods;
  int workers;
  bool assigned = false;
  bool workerAssigned = false;
};
