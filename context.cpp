#include "context.h"

#include <iostream>
using namespace std;

// 0 == wall, 1 == empty, 2 == contains can

Context::Context (  ) {
  current = 0;
  north = 0;
  east = 0;
  south = 0;
  west = 0;
  coding = 0;
}

void Context::encode ( void ) {
  if ( coding > 242 )
    cout << endl << "CONTEXT:encode: error in coding: " << coding;
  coding = current * 3*3*3*3 + north * 3*3*3 + east * 3*3 + south * 3 + west;
}

int Context::getCoding ( void ) {
  return coding;
}

void Context::getContext (int& c, int& n, int& e, int& s, int&w ){
  c = current; n=north; e=east; s=south; w=west;
}

void Context::printContext ( void ) {
  cout << " current " << current << " north " << north << " east " << east << " south " << south << " west " << west << endl;
  cout << "coding:" << coding; 
}

void Context::setContext ( int c , int n , int e , int s , int w ) {
    current = c; north=n; east=e; south=s; west=w;
    encode();
}
