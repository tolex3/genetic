#include "strategy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Strategy::Strategy ( ) {
  for ( int i = 0; i < 243; i++ )
    strategyImplementation [ i ] = 0;
  
  score = -1000000; // flag
  mutationCount = 0;
  birthGeneration = -1 ; // flag
}

int Strategy::element ( int index ) {
  return strategyImplementation [ index ];
}

void Strategy::writeStrategy ( int sArray [ ] ) {
  for ( int i = 0; i < 243; i++ ) {
    strategyImplementation [ i ] = sArray [ i ] ;
  }
}

void Strategy::printStrategy ( ) {
  cout << endl;
  for ( int i = 0; i < 243; i++ ) {
    cout<< " " << i << " => " << strategyImplementation [ i ];
    if ( ( i > 0 ) && (i % 10 == 0 ) )
      cout << endl;
  }
}

void Strategy::setRandomStrategy ( ) {

  for ( int i = 0; i < 243; i++ ) {
    strategyImplementation [ i ] = rand ( ) % 7;
  }
    
}

Strategy* copulate (Strategy l, Strategy r ) {

  int cutPoint = rand() % 243;
  Strategy *childStrategy = new Strategy;
  
  for ( int i = 0; i < cutPoint; i++ ) 
    childStrategy -> strategyImplementation [ i ] = l.strategyImplementation [ i ];
  
  for ( int i = cutPoint; i < 243; i ++ )
    childStrategy -> strategyImplementation [ i ] = r.strategyImplementation [ i ];
  
  return childStrategy;  
}

int Strategy::getAction ( int index ) {
  return strategyImplementation [ index ];
}

// NOTE! not safe for a=a!
Strategy& Strategy::operator = ( const Strategy& rhs ) {
    if (this != &rhs) {
      // Deallocate, allocate new space, copy values...
      for ( int i = 0; i < 243; i++ ) {
	strategyImplementation [ i ] = rhs.strategyImplementation [ i ];
      }
      score = rhs.score;
      birthGeneration = rhs.birthGeneration;
      mutationCount = rhs.mutationCount;
    }
    return *this;

}

void Strategy::mutate ( void ) {
  int mutationPoint = rand() % 243;
  int newAction = rand() % 7;
  strategyImplementation [ mutationPoint ] = newAction;
}

bool identical ( Strategy l, Strategy r, int& diffPos ) {
  for ( int i = 0; i < 243; i++ ) {
    if ( l.strategyImplementation [ i ] != r.strategyImplementation [ i ] ) {
      diffPos = i;
      return false;
    }
  }
  return true;
}

 int similarityCount ( Strategy l, Strategy r) {
  int count = 0;
  for ( int i = 0 ; i < 243; i++)
    if ( l.strategyImplementation [ i ] == r.strategyImplementation [ i ] )
      count++;
  return count;
}

void Strategy::updateScore ( int newScore ) {
  score = newScore;
}


int Strategy::getScore ( void ) {
  return score;
}

void Strategy::updateMutationCount ( void ) {
  mutationCount++;
}

void Strategy::setBirthGeneration ( int generation ) {
  birthGeneration = generation;
}

int Strategy::getBirthGeneration ( void ) {
  return birthGeneration;
}

int Strategy::getMutationCount ( void ) {
  return mutationCount;
}


