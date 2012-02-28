#ifndef CONTEXT_H
#define CONTEXT_H

class Context {

 private:
  int current;
  int north;
  int east;
  int south;
  int west;
  int coding;
  void encode ( void );

 public:
  Context ( );
  void setContext ( int c, int n, int e, int s, int w );
  int getCoding ( void );
  void getContext ( int& c, int& n,int& e,int& s, int& w );
  
  // DEBUG
  void printContext ( void );
};
#endif
