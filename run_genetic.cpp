#include "robby.h"
#include "context.h"
#include "strategy.h"
#include "constants.h"
#include "strategyStore.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Max theoretical score: 500 (~50 cans x 10 points)
// worst theoretical score: -5 * STEPS  = -1000 with 200 steps

// The point of this program is to illustrate how an algorithm
// can modify its behavior by learning and adapting during evolution.

// Obviously a good algorithm designer, with external knowledge of the 
// system, the robot's position, and environment and constraints  could design an algorithm that can avoid
// bouncing into walls etc, but the point is that Robby has no other knowledge of
// the system than his current context, i.e. he does not know how large the system is, 
// what shape it is, or any other information except his current context. 
// Thus, instead of the programmer with intrinsic knowledge designing an algorithm for
// Robby, the programmer defines the evolution rules, and let's the program itself figure
// out an optimal algorithm.

Robby agentArray [ NR_AGENTS ];
Strategy s;
StrategyStore st;

int main ( void ){

  int genCounter = 0;
  int populationCount = 0;
  int sessionScores = 0;
  int fieldMatrix [ 10 ] [ 10 ];

  srand ( time ( NULL ) );

  // initialize agents

  for ( int agent = 0; agent < NR_AGENTS; agent++ ) {
    s.setRandomStrategy ( );
    agentArray [ agent ].setStrategy ( s );
  }

  while ( genCounter < GENERATIONS ) {

    for ( int agent = 0; agent < NR_AGENTS; agent++ ) {

      agentArray [ agent ].resetStatistics ( );

      for ( int session = 0; session < SESSIONS; session++ ) {
	
	agentArray [ agent ].setPos ( 0 , 0 );
	agentArray [ agent ].initializeField ( fieldMatrix ) ;
	agentArray [ agent ].resetStatistics ( );

	for ( int steps = 0; steps < STEPS; steps++ ) {

	  // make one step by figuring out current context, getting the index for that context, getting the action for that index 

	  agentArray [ agent ].updateContext( );
	  agentArray [ agent ].makeMove ( agentArray [ agent ].getStrategy( ).getAction ( agentArray [ agent ].getContext( ).getCoding( ) ), false );

	} // end steps

	// register score for this session

	sessionScores  += agentArray [ agent ].getPoints ( );

      } // END SESSIONS(k): all sessions for an agent done

      int sessionAvg = 0;

      sessionAvg = sessionScores / SESSIONS;
      sessionScores = 0;
 
      agentArray [ agent ].getStrategy ( ).updateScore ( sessionAvg );
    
    } // end agents

    for ( int i = 0; i < NR_AGENTS; i++ ) {
      // cout << endl << "agent session scores:" << "agent:" << i << " " << agentArray [ i ].getStrategy ( ).getScore ( );

      if ( ! (st.exists ( agentArray [ i ].getStrategy ( ) ) ) )
	st.addStrategy ( agentArray [ i ].getStrategy ( ) );
    }

    populationCount = 0;
    Strategy survivors [ SURVIVORS ];
    
    for ( int performers = 0; performers < SURVIVORS; performers++) {
      st.getOne ( survivors [ performers ], performers );
      agentArray [ performers ].setStrategy ( survivors [ performers ] );

      if ( rand () % 100 == 0 ) {
	agentArray [ populationCount ].getStrategy ( ).mutate ( );
	agentArray [ populationCount ].getStrategy ( ).updateMutationCount ( );
      }
	
      populationCount++;
    }

    while ( populationCount < NR_AGENTS ) {
      int father = 0; int mother = 1;
      Strategy *temp;

      // first child for one parent pair
      //
      temp =  copulate ( survivors [ father ], survivors [ mother ] );
      agentArray [ populationCount ].setStrategy ( *temp );
      agentArray [ populationCount ].getStrategy ( ). setBirthGeneration ( genCounter ) ;
      delete temp;

      // second child for one parent pair
      //
      temp =  copulate ( survivors [ mother ], survivors [ father ] );
      agentArray [ populationCount ].setStrategy ( *temp );
      agentArray [ populationCount ].getStrategy ( ). setBirthGeneration ( genCounter ) ;
      delete temp;
      
      // mutate a fraction of the children
      //
      if ( rand () % 4 == 0) {
	agentArray [ populationCount ].getStrategy ( ).mutate ( );
	agentArray [ populationCount ].getStrategy ( ).updateMutationCount ( );
      }
      
      // decrease the likelihood of lower performing parents to breed
      //
      if ( rand ( ) % 10 == 0 ) {
	father +=2; mother += 2;
      }

      populationCount++;
    }
    
    
    if ( genCounter % 10 == 0 ) {
      st.printStore ();
      cout << endl << "generation average similarity:" << st.averageSimilarity () << endl;
    }

    if (genCounter < GENERATIONS -1)
      st.resetRanks ( );

    genCounter++;
    
  } // end generations
    
  cout << endl << " FINAL RANKINGS after " << genCounter << " generations " << endl;
  st.printStore ( );

  // testrun the winning strategy for same number of sessions as the generations did
  //
  
  Robby winningAgent;
  Strategy winner;
  st.getOne ( winner, 0);
  int winnerScore = 0;

  winningAgent.setStrategy ( winner );
  winningAgent.getStrategy ( ).printStrategy ( );

  cout << endl << "WINNERS RANK SCORE: " << winner.getScore ( ) << " BIRTHGEN: " << winner.getBirthGeneration ( ) << " MUTATIONS: " << winner.getMutationCount ( ) ;
  
  for ( int nr_sessions = 0; nr_sessions < SESSIONS; nr_sessions++ ) {
    cout << endl << "Starting session: " << nr_sessions ;
    winningAgent.setPos ( 0 , 0 );
    winningAgent.initializeField ( fieldMatrix );
    winningAgent.resetStatistics ( );
    
    for ( int steps = 0; steps < STEPS; steps++) {
      winningAgent.updateContext ( ) ;
      winningAgent.makeMove ( winningAgent.getStrategy( ).getAction ( winningAgent.getContext( ).getCoding( ) ) , false );
    }

    winnerScore += winningAgent.getPoints ( );
  }
  
  winnerScore = winnerScore / SESSIONS;

  cout << endl << " WINNER'S testrun average score: " << winnerScore;
}



