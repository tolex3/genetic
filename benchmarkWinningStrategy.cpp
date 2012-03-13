// 2DO: om robby står på en ruta med en burk, och inte plockar upp den, 
// så kommer burksymbolen ändå att bytas ut till en punkt. Borde lägga 
// in en check på att om action != plocka upp, så ska burksymbolen inte 
// skrivas över.

#include "robby.h"
#include "context.h"
#include "strategy.h"
#include "constants.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>

#include <getopt.h>
#include <stdio.h>

using namespace std;

int hundredGenStrategy [ ] = {1,1,5,4,3,4,0,6,3,1,3,0,4,2,5,5,5,1,6,5,5,0,6,4,6,5,4,1,1,3,6,1,0,4,4,0,4,2,4,0,0,5,5,4,6,1,4,2,3,4,6,0,1,1,1,0,6,2,1,3,6,0,0,1,5,1,0,0,1,1,2,2,4,4,0,2,1,4,0,6,5,5,0,4,3,2,3,2,0,2,6,1,5,5,2,1,5,4,5,6,5,4,5,5,1,5,4,6,1,3,2,5,1,1,3,3,3,6,6,2,6,5,4,6,3,0,0,2,2,5,5,5,5,3,6,0,6,2,2,1,1,1,0,4,6,5,3,5,5,3,6,6,0,5,6,0,5,0,4,2,4,3,2,1,6,0,2,5,6,5,0,3,2,2,4,2,1,4,3,4,3,5,2,5,4,5,1,4,4,0,1,0,3,5,3,2,4,5,1,3,6,1,3,4,4,6,3,5,4,3,0,0,1,1,1,0,4,1,1,0,6,6,3,5,5,1,1,1,6,1,5,4,2,0,1,4,2,1,3,2,1,1,3,2};

int thousandGenStrategy [ ] = {2,1,5,6,3,4,4,3,6,2,1,3,3,4,5,0,1,6,4,0,3,6,2,6,6,2,5,4,4,0,3,2,1,0,6,6,5,5,2,4,5,6,5,6,3,6,6,3,0,5,1,3,1,1,3,5,6,0,3,6,6,4,2,0,5,1,1,6,2,4,5,1,6,3,0,4,5,6,2,4,3,3,5,0,6,2,0,6,4,3,2,4,0,2,5,4,2,0,1,0,3,4,2,3,6,2,2,2,1,6,1,1,4,3,6,0,1,0,3,5,2,1,2,2,2,3,0,2,3,2,2,3,2,6,6,2,5,3,4,6,0,1,1,0,6,6,2,1,1,4,2,6,5,6,2,2,5,2,3,0,4,1,1,1,3,5,0,4,0,6,1,0,3,4,4,6,2,4,6,4,3,3,4,4,1,6,4,6,0,6,4,3,5,1,0,6,0,4,4,5,5,4,0,2,4,3,2,4,1,3,4,5,6,4,4,6,0,3,1,5,2,1,1,1,6,4,2,5,6,1,5,3,2,2,4,2,1,0,1,2,0,3,4};

int tenKGenStrategy [ ] =  {1,0,0,2,2,6,4,0,6,3,5,3,1,5,2,2,1,6,1,4,0,0,2,0,3,0,1,3,0,5,1,3,4,2,4,2,1,4,2,0,4,1,6,1,0,6,6,1,4,1,0,3,5,1,4,1,2,0,0,6,2,2,5,1,3,6,4,0,5,3,3,6,2,2,2,4,0,5,1,5,3,6,2,1,6,1,2,5,3,2,3,2,4,2,2,6,2,4,3,3,5,5,2,2,3,2,2,2,3,6,3,4,2,3,5,2,3,5,6,3,1,1,3,1,1,6,0,6,3,2,2,6,2,2,3,6,5,0,6,2,6,4,2,3,1,1,0,2,0,3,2,0,1,6,6,0,6,0,3,0,0,0,4,0,2,5,6,4,5,6,4,5,6,4,4,4,3,4,1,0,4,4,4,4,4,6,4,4,4,6,4,3,5,4,4,5,4,4,0,3,4,4,4,4,4,3,2,5,4,6,1,1,1,4,1,2,4,1,2,6,4,4,2,5,4,0,4,4,0,4,4,0,2,2,3,4,4,6,1,1,1,1};

int hundredKStrategy [ ] = {4,3,5,0,4,3,1,3,6,2,6,2,1,0,5,2,5,2,1,0,0,1,0,3,6,4,6,4,0,4,2,4,6,4,3,4,3,6,5,2,6,4,6,2,0,2,0,5,2,1,4,6,1,4,6,4,6,6,1,6,2,3,0,6,2,1,1,6,5,2,1,6,4,4,0,1,0,0,6,3,1,0,3,6,3,2,5,2,2,6,0,6,6,1,1,6,1,2,3,6,4,2,1,1,1,1,1,6,4,3,3,0,2,3,3,2,3,0,0,0,0,3,3,2,2,2,1,0,4,1,6,3,1,6,3,0,3,6,1,0,2,0,0,3,2,1,2,0,0,0,0,0,0,0,3,6,0,1,3,0,4,6,5,6,2,0,4,4,2,4,2,0,0,5,4,4,4,2,4,3,0,5,3,4,4,4,4,4,3,3,4,4,1,4,4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,1,1,1,1,4,4,4,0,2,4,0,5,0,6,3,4,2,1,5,4,4,4,4,4,4,6,1,3,1,4,1,1,4};

int topStrategy [ ] = {0,4,3,0,0,3,5,4,4,0,0,4,0,4,3,4,0,0,3,1,1,0,1,4,3,1,0,0,2,1,5,0,4,3,3,3,1,1,2,3,5,0,4,3,3,4,2,2,4,0,2,2,0,0,1,5,3,5,2,3,1,0,2,1,4,2,3,4,3,2,5,1,4,4,5,3,1,4,5,2,2,3,4,1,3,3,3,1,1,1,3,1,1,2,2,2,2,0,1,3,2,3,2,4,2,2,1,2,5,0,1,4,0,3,2,4,3,1,1,1,2,3,3,2,2,2,1,1,4,2,1,3,2,2,4,4,0,4,2,0,3,1,2,5,5,0,3,5,0,0,0,2,2,0,1,3,5,2,2,5,1,4,3,1,5,1,4,4,3,2,3,3,5,2,4,4,4,4,1,4,5,1,5,4,1,4,4,1,2,0,4,3,3,4,4,3,2,4,4,4,3,4,4,4,4,4,4,4,4,0,4,1,1,4,1,1,0,4,0,0,4,4,2,4,2,1,4,0,2,4,4,4,4,4,3,4,1,3,4,1,1,5,1};

int main(int argc, char **argv) {

  Robby agent;
  Strategy fiftyKGen;
  Strategy random;
  Strategy hundredGen;
  Strategy thousandGen;
  Strategy tenKGen;
  Strategy hundredKGen;

  int cc;
  int nr_steps = 20;
     
       while (1)
         {
           static struct option long_options[] =
             {
//               {"Number of agents",     required_argument,       0, 'a'},
//               {"Number of cleaning sessions",  required_argument,       0, 'c'},
//               {"Number of survivors",  required_argument, 0, 'n'},
               {"Number of steps in each cleaning session",  required_argument, 0, 's'},
               {0, 0, 0, 0}
             };
           /* getopt_long stores the option index here. */
           int option_index = 0;
     
           cc = getopt_long (argc, argv, "s:",
                            long_options, &option_index);
     
           /* Detect the end of the options. */
           if (cc == -1)
             break;
     
           switch (cc)
             {
             case 0:
               printf ("option %s", long_options[option_index].name);
               if (optarg)
                 printf (" with arg %s", optarg);
               printf ("\n");
               break;
             case 's':
               printf ("option -%c with value `%s'\n", cc, optarg);     
               nr_steps = (int) atol(optarg);
               break;
//             case 'a':
//             case 'n':      
//             case 'c':
//               printf ("option -%c with value `%s'\n", cc, optarg);     
//               break;
             case '?':
               /* getopt_long already printed an error message. */
               break;
     
             default:
               abort ();
             }
         }

  fiftyKGen.writeStrategy ( topStrategy );
  hundredGen.writeStrategy ( hundredGenStrategy );
  thousandGen.writeStrategy ( thousandGenStrategy );
  tenKGen.writeStrategy ( tenKGenStrategy );
  hundredKGen.writeStrategy ( hundredKStrategy );
  
  srand (time (NULL));

  int score = 0;
  int matrix1 [ 10 ] [ 10 ];
  bool fiftyKActive, hundredActive, thousandActive, tenKActive, hundredKActive, randomActive;
  int c, n, e, s, w, x_pos, y_pos, x_old, y_old, action, old_c, old_action;
  char trackMarker = 'X';

  agent.setStrategy ( fiftyKGen );
  agent.getStrategy ( ).printStrategy ( );

  for ( int nr_sessions = 0; nr_sessions < SESSIONS; nr_sessions++ ) {
    cout << endl << "Starting session: " << nr_sessions ;

    hundredActive = false;thousandActive = false; tenKActive = false;fiftyKActive = false; randomActive = false;

    switch ( nr_sessions ) {
    case 0:
      random.setRandomStrategy ( );
      agent.setStrategy ( random );
      randomActive= true;
      break;
    case 1:
      agent.setStrategy ( hundredGen );
      hundredActive = true;
      break;
    case 2:
      agent.setStrategy ( thousandGen );
      thousandActive = true;
      break;
    case 3:
      agent.setStrategy ( tenKGen );
      tenKActive = true;
      break;
    case 4:
      agent.setStrategy ( fiftyKGen );
      fiftyKActive = true;
      break;
    default:
      agent.setStrategy ( hundredKGen );
      hundredKActive = true;
    }

    agent.setPos ( 0 , 0 );
    agent.initializeField ( matrix1 );
    
    initscr();
    clear();
    
    mvhline (10,0,'-',10);
    mvvline (0,10,'|',10);

    if ( fiftyKActive )
      mvprintw (30,0, "FIFTTYKGEN RUNNING");
    if ( hundredActive )
      mvprintw (30,0, "HUNDRED RUNNING");
    if (thousandActive )
      mvprintw (30,0, "THOUSAND RUNNING");
    if (tenKActive )
	mvprintw (30,0, "TENTHOUSAND RUNNING");
    if ( hundredKActive )
	mvprintw (30,0, "HUNDRED-K RUNNING");
    if ( randomActive )
      mvprintw (30,0, "RANDOM RUNNING");
    
    for ( int y = 0; y < 10; y++ )
      for ( int x = 0; x < 10; x++ ){
	if ( matrix1 [ x ] [ y ] == 2 ){
	  mvprintw(y,x,"O");
	}
      }
      agent.resetStatistics ( );
    
    for ( int steps = 0; steps < nr_steps; steps++) {
      agent.updateContext ( ) ;
      
      agent.getContext().getContext ( c, n, e, s, w );
      action = agent.getStrategy ( ).getAction ( agent.getContext ( ).getCoding ( ) );
 
      mvprintw ( 15, 30, "ROBBYS CURRENT CONTEXT");
      mvprintw ( 18, 40, "%d", c);
      mvprintw ( 17, 40, "%d", n);
      mvprintw ( 18, 41, "%d", e);
      mvprintw ( 19, 40, "%d", s);
      mvprintw ( 18, 39, "%d", w);
      mvprintw ( 23, 36, "ACTION: %d", action);

      agent.getPos ( x_pos , y_pos );

      //mvprintw ( y_pos , x_pos , " ");
      attron ( A_BOLD );
      if ( c == 2 )
	mvprintw (y_pos, x_pos, "*");
      else
	mvprintw ( y_pos , x_pos ,"%c", trackMarker);
      
      attroff ( A_BOLD );
      
      if (  ( ( old_c == 2 ) && ( old_action != 4 ) ) ) {
	mvprintw (y_old, x_old,"o");
      }
      else 
	if ( old_c == 2 )
	  mvprintw (y_old, x_old, "x");

      else {
	//	mvprintw (y_old, x_old, " ");
	mvprintw (y_old, x_old, ".");
      }

      mvprintw ( 15,0, "STEPS: %d", steps);
      mvprintw ( 21,0, "CURRENT POINTS: %d", agent.getPoints ( ));
      mvprintw ( 26,0, "CURRENT PENALTIES: %d", agent.getPenalties ( ));

      x_old = x_pos; y_old = y_pos; old_c = c; old_action = action;
  
      mvprintw ( 21, 36, "CODING:     "); // to clear up if previous code was longer than next
      mvprintw ( 21, 36, "CODING: %d", agent.getContext( ).getCoding ( ));

      agent.makeMove ( agent.getStrategy( ).getAction ( agent.getContext( ).getCoding( ) ) , false );

      refresh();			
      getch();
      //sleep (1);
    }
    endwin();
    
    score += agent.getPoints ( );
  }
  
  score = score / SESSIONS;

  cout << endl << " AGENTS'S testrun average score: " << score;
  
}
