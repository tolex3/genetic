#include <iostream>

#include "strategyStore.h"

using namespace std;

void StrategyStore::sortStrategies ( Strategy strArray [], int size ) {
  Strategy tempStrategy;

  for (int i = 0; i < size - 1; i++ ) {
    for (int j = i + 1; j < size; j++) {
      if (strArray [ j ].getScore ( ) > strArray [ i ].getScore ( ) ){
	tempStrategy = strArray [ j ];
	strArray [ j ] = strArray [ i ];
	strArray [ i ] = tempStrategy;
      }
    }
  }
}

void StrategyStore::addStrategy ( Strategy& s ) {
  Strategy old;
  int position = 0;
  bool done = false;

  sortStrategies ( strategies , NR_AGENTS );

  for ( int i = 0; i <  NR_AGENTS; i++ ) {
    if ( s.getScore ( ) > strategies [ i ].getScore( ) ) {
      position = i;
      old = strategies [ position ];
      strategies [ position ] = s;
      
      for ( int j = NR_AGENTS - 1; j > position + 1; j-- ) {
	strategies [ j ] = strategies [ j - 1];
      }
      
      strategies [ position + 1 ] = old;
      break;
    }
  }
}

void StrategyStore::printStore ( void ) {
  
  for ( int i = 0; i < NR_AGENTS; i++ ) {
    //cout << endl << " position: " << i << " " << strategies [ i ].getScore ( ) << " birthGen: " << strategies [ i ].getBirthGeneration ( );
    //cout << " mutationCount: " << strategies [ i ].getMutationCount ( ) ;
    // strategies [ i ].printStrategy ( );
  }
  cout << endl << " PrintStore::generation top session score: " << strategies [ 0 ].getScore ( ) << endl;
}

void StrategyStore::getOne ( Strategy& str, int rank ) {
  
    str = strategies [ rank ];
  
}

void StrategyStore::resetRanks ( void ) {
  for ( int i = 0; i < NR_AGENTS; i++ )
    {
      strategies [ i ].updateScore ( -5555555 );
    }
}

int StrategyStore::calculateGenerationAverage ( ) {
  int sum = 0;
  for ( int i = 0; i < NR_AGENTS; i++) {
    sum += strategies [ i ].getScore ( );
  }
  return ( sum / NR_AGENTS );
}

int StrategyStore::averageSimilarity () {
  int simiCount = 0;
  int comparisons = 0;

  for ( int i = 0; i < NR_AGENTS - 1; i++ ) {
    for ( int j = i + 1; j < NR_AGENTS; j++ ){
      simiCount += similarityCount ( strategies [ i ], strategies [ j ] );
      comparisons++;
    }
  }
  return simiCount / comparisons;
}

bool StrategyStore::exists (Strategy& str) {
  bool diffFound; 
  int diffPos;

  for (int j = 0; j < NR_AGENTS; j++) {
    if ( identical (str, strategies [ j ], diffPos ) )
      return true;
  }
  return false;
}
