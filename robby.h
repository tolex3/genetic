#ifndef ROBBY_H
#define ROBBY_H

#include "context.h"
#include "strategy.h"

class Robby {

 private:
  int field [ 10 ] [ 10 ];
  int remainingMoves;
  int x_pos;
  int y_pos;
  Context context; 
  Strategy strategy;
  int cansCollected;
  int penalties;
  int points;
 
 public:
  Robby( );
  void initializeField ( int matrix [10][10] );
  void updateContext ( void ); 
  bool makeMove ( int action, bool showMoves );
  int getCansCollected ( void );
  int getPenalties ( );
  int getPoints ( );
  void setStrategy ( Strategy& s );
  Strategy& getStrategy ( );
  void resetStatistics ( void );
  void setPos( int x , int y );
  void getPos ( int& x, int& y );

  //

  void printField ( void );
  void printPos ( void );
  void setContext ( Context ); // not used, should probably use ref
  Context& getContext ( void ); 
 
};
#endif
