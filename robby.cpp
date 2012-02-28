#include "robby.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Robby::Robby( ) {
  x_pos = 0;
  y_pos = 0;
  cansCollected = 0;
  penalties = 0;
  points = 0;   
}

void Robby::setPos (int x , int y ) {
  x_pos = x;
  y_pos = y;
}

void Robby::initializeField ( int matrix [10] [10] ) {
  
  int cans = 0;
  for ( int i = 0; i < 10; i++ ) {
    for ( int j = 0; j < 10; j++ ) {
      field [ j ] [ i ] = 1;
      if ( ( rand() % 2 == 0 ) && ( field [ j ] [ i ] == 1 ) && ( cans < 50 ) ) { // ca 50 av rutorna blir burkar
	field [ j ] [ i ] = 2;
	cans++;
#ifdef DEBUG
	  // cout << endl << "in Robby::initField: placing can at " << j << "," << i;
#endif
      }
    }
  }
  
  for ( int m = 0; m < 10; m++ )
    for ( int n = 0; n < 10; n++ )
      matrix [ n ] [ m ] = field [ n ][ m ];
}

void Robby::setStrategy ( Strategy& s ){
  strategy = s;
}

Strategy& Robby::getStrategy ( ) {
  return strategy;
}


// 0 is wall, 1 is empty, 2 denotes can

bool Robby::makeMove ( int action, bool showMoves = false ) {
  int c, n, e, s, w;

 int x_increment = ( rand () % 2 ) - 1;
 int y_increment = ( rand () % 2 ) - 1;

  context.getContext ( c , n , e , s , w );

  if ( showMoves ) {
    cout << endl << "ROBBY: current position:";  printPos ( );
    cout << " context: c:" << c <<" n:" << n << " e:" << e << " s:" << s << " w:" << w ;
    cout << " taking action:" << action << endl;
  }

  switch ( action ) {
  case 0: // move N
    if ( !( n == 0 ) ) {  
      // if not wall in north
      y_pos--;
    }
    else {
      penalties++;
      points -= 5;
    }
    break;
  case 1: // move E
    if ( ! ( e == 0 ) )
      x_pos++;
     else {
       penalties++;
       points -= 5;
     }
    break;
  case 2: // move S
    if ( ! ( s == 0 ) )
      y_pos++;
 else {
   penalties++;
   points -= 5;
 }
    break;
  case 3: // move W
    if ( ! ( w == 0 ) )
      x_pos--;
 else {
   penalties++;
   points -= 5;
 }
    break;
  case 4: // pickup
    if ( field [ x_pos ] [ y_pos ] == 2 ) {
      cansCollected++;
      points += 10;
      field [ x_pos ] [ y_pos ] = 1;
#ifdef DEBUG
      // cout << endl << "Robby::makemove picking up at " << x_pos << "," << y_pos;
#endif
    }
    else {
      penalties++;
      points--;
    }
    break;
    case 5: // do nothing
    ;
    break;
  case 6: // random move
   
    if ( ( x_pos + x_increment < 0) || ( x_pos + x_increment > 9) || ( y_pos + y_increment < 0 ) || ( y_pos + y_increment > 9)) {
      // wall would be hit
      penalties++;
      points -= 5;
    }
    else {
      x_pos = x_pos + x_increment;
      y_pos = y_pos + y_increment;
    }
    break;
  default:
    cout << endl << "ROBBY::makeMove: error in action: " << action;
  }
 
}

int Robby::getPoints ( ) {
  return points;
}

int Robby::getPenalties ( ) {
  return penalties;
}

int Robby::getCansCollected ( void ) {
  return cansCollected;
}

void Robby:: printField ( void ){
  int i, j;
  cout << endl;
  for ( i = 0; i < 10; i++ ) {
    for ( j = 0; j < 10; j++ ) {
      cout  << field [ j ] [ i ] << " ";
    }
    cout << endl;
  }
}

void Robby::updateContext ( void ) {
  // flag all neighbors + current as empty

  int c = 1;
  int n = 1;
  int e = 1;
  int s = 1; 
  int w = 1;

  bool n_is_wall = false;
  bool e_is_wall = false;
  bool s_is_wall = false; 
  bool w_is_wall = false;

  // check for walls 
  if ( x_pos - 1 == -1 ){
    w = 0; // wall in west
    w_is_wall = true;
  }
  if ( x_pos + 1 == 10 ) {
    e = 0; // wall in east
    e_is_wall = true;
  }
  if ( y_pos - 1 == -1 ) {
    n = 0; // wall in north
    n_is_wall = true;
  }
  if ( y_pos + 1 == 10 ){
    s = 0; // wall in south
    s_is_wall = true;
  }

  if ( field [ x_pos ] [ y_pos ] == 2 )
    c = 2; // current contains can
  
  if ( ! e_is_wall && ( field [ x_pos + 1 ] [ y_pos ] == 2 ) )
    e = 2; // east contains can

  if ( ! s_is_wall && ( field [ x_pos ] [ y_pos + 1 ] == 2 ) )
    s = 2; // south contains can

  if ( ! w_is_wall && ( field [ x_pos - 1 ] [ y_pos ] == 2 ) )
    w = 2; // west contains can
  
  if ( ! n_is_wall && ( field [ x_pos ] [ y_pos - 1 ] == 2 ) )
    n = 2;

  context.setContext ( c , n , e , s , w );
}

void Robby::printPos ( void ) {
  cout << endl << " current position: x:" << x_pos << " y:" << y_pos;
}

void Robby::setContext ( Context c ) {
  context = c; 
}

Context& Robby::getContext ( void ) {
  return ( *this ).context;
}

void Robby::resetStatistics ( void ) {
  points = 0; 
  penalties = 0;
  cansCollected = 0;
}

void Robby::getPos ( int& x, int& y ) {
  x = x_pos; y = y_pos;
}
