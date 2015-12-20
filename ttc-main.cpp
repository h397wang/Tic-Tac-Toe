
#include <iostream>
#include "state.h"
#include "list.h"

using namespace std;

// currently, seems to go for an infinite loop if there are less than two entries in the constructor;??
// incorporate the alpha beta pruning to eliminate unneccesary calculations
// might be the solution
int main(){


	// letting the player be 1 and the computer be  2
	int game[3][3] = {{0,1,0},
					  {0,2,0},
					  {0,0,0}};
	int x,y;
	
	State *ptr = new State(game);
	ptr->printBoard();
	
	while (!ptr->aWinner()){
		
		if (ptr->getDepth()%2 == 0){
			
			while (!ptr->aMove()){
				;
			}
			
		}else{
			
			ptr->decide();
		}
		
	}
	
	
}
