#ifndef STRATEGYSTORE_H
#define STRATEGYSTORE_H

#include "constants.h"
#include "strategy.h"

class StrategyStore {

 private:

  Strategy strategies [ NR_AGENTS ];

  void sortStrategies ( Strategy strArray [] , int size ); 

 public:

  void addStrategy ( Strategy& s );
  void getOne ( Strategy& str, int rank );
  void resetRanks ( void );
  int calculateGenerationAverage ( );
  int averageSimilarity ();
  bool exists ( Strategy& str);

  // DEBUG
  void printStore ( void );
};
#endif
