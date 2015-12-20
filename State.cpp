#include "state.h"
#include <math.h>
#include <assert.h>
#include <iostream>

#include "list.h"

using namespace std;

#define DEBUG 0

State::State(int setup[3][3]){
	// this version of the constructor copies in the board
	// it is used by createSubStates function
	
	if (DEBUG) {cout << "Main constructor called " << endl; }
	
	// copy in the array
	int moves = 0;
	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
				
			board[row][col] = setup[row][col];
			if (board[row][col] != 0){
				moves++;
			}
			
			// now all of the children have the same values for board
			// place the different moves...
		
		}
	}
	
	children = NULL;
	next = NULL;
	depth = moves;
	
}

State::State(){
	// new game
	// blank board
	cout << "Starting a new game of Tic Tac Toe" << endl;
	depth = 0;
	
	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			board[row][col] = 0;
		}
	}
	
	children = NULL;
	next = NULL;
	
}

State::~State(){
	//cout << "Destructor called for this State" << endl;
	
	// destructor deletes all of its children before deleting itself
	if (children == NULL){
		delete children;
		delete next;
	}else{ // delete its children first
	
		State *current = children;
		
	// cycle through the linked list and delete it all
		while (current != NULL){
			State *temp = current;	
			current = current->next;
			delete temp;
		}
	}	
}



void State::createSubStates(){
	/*
	depending on the depth of the state, create the corresponding number of sub-states
	the children pointer is the head to a linked list of sibling states
	sibling states can access each other via next
	both children and sibling pointers are instantiated to NULL on construcion
	use the board copy constructor for each sub state created
	then place the corresponding moves
	*/
	
	if (DEBUG){ cout << "Creating new sub states " << endl; }
	
	// for the first child;
	children = new State(board);
	//cout << "Creating the header pointer, do not consider this state " << endl;
	// for each consecutive
	State *current = children; // this is just like a header..
	
	// for each blank spot, make a distinct move 
	int j = 0; // counter for t  he move Number??
	
	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			if (board[row][col] == 0){
				
				current->next = new State(board);
				current = current->next;
				current->placeMove(row, col); // say we arrive at the first blank, place move there
				
				if (DEBUG){ cout << "the address of this substate is " << current << endl; }
				// problem: consider the last move to be placed, an extra node is then created?
				
				//current->printBoard();
			}
		}
	}
	
}

bool State::isComplete(){
	
	// this is used by the minimax, but I want an ingame one...
	/*
	
	Returns true if it's a leaf node (aka depth 8) or if there is a winner, it modifies it's score value
	so that getScore can return it
	Else it returns false

	*/
	if (DEBUG){ cout << "isComplete() called " << endl; }
	
	int output;
	// check diagnals
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0){

		if (DEBUG){ cout << "Player " << board[0][0] << "is the winner" << endl; }
		
		score = (board[0][0] == 2? 10 : -10); // should be done from the computer's perspective, so if the winner is player 1, -10.
												//assuming player 2 is the comp
		if (score < 0){
			score += depth;
		}
		
		return true;
		
	// check other diagnal	
	}else if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != 0){
	
		if (DEBUG){ cout << "Player " << board[2][0] << " is the winner" << endl; }
		score = (board[2][0] == 2? 10 : -10);
		if (score < 0){
			score += depth;
		}
		return true;
	
	// check rows and cols	
	}else{
	
		for (int i = 0; i < 3; i ++){
			
			// check rows
			if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != 0){
			
				// then there's a winner?		
				if (DEBUG){ cout << "Player " << board[i][0] << " is the winner" << endl; }
				score = (board[i][0] == 2? 10 : -10);
				if (score < 0){
					score += depth;
				}
				return true;
			
			// now check columns
			}else if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != 0){
			
				// then there's a winner
				if (DEBUG){ cout << "Player " << board[0][i] << " is the winner" << endl; }
				score = (board[0][i] == 2? 10 : -10);
				if (score < 0){
					score += depth;
				}
				return true;
			}		
		}
		
		if (depth == 9){
			// then this state must be a tie
			score = 0;
			return true;
		}
	
		return false;
	}
			
}


void State::decide(){
	
	if (DEBUG){ cout << "decide() called " << endl; }
	/*
	this function is the AI. for each of the states children, use getScore and keep track of which one is the best
	then use placeMove or whatever to do so and progress the game to the other players turn
	*/
	// initiate 
	createSubStates();
	State *current = children->next;
	State *best = children->next; // the children pointer isnt actually a state, its just a header	
	List<int> theList;

	// these two start off as the same?
	int currentScore = current->getScore();
	int bestScore = best->getScore();
	
	theList.insertAtBack(currentScore);
		
	current = current->next;
		
	while (current != NULL){
		
		if (DEBUG){
		cout << "Considering this state option" << endl;
		current->printBoard();
		cout << "Comparing this childs score with best score \n\n\n\n" << endl;
		}
		currentScore = current->getScore();
		theList.insertAtBack(currentScore);
		
		if (DEBUG){ cout << "currentScore is " << currentScore << " and bestScore is " << bestScore << endl;}
		
		
		if (currentScore > bestScore) { // computer is player two, so pick max from the list
			
			bestScore = currentScore;
			best = current;
			
			//cout << "the new best is ";
			//best->printBoard();
			
		}
		
		//cout << "current is incremented from " << current << " to " << current->next << endl;
		
		current = current->next;
		 
	}
	
	if (DEBUG){
		cout << "The best move is this state ptr " << best << endl;
		//copy the new board.. or make the move..
		cout << "decide() is considering from the scores list" << endl;
		theList.print();
	}
	aMove(best);
	
}

int State::getScore(){ // aka minimax
	
	/*
	This is the recursive function. The Base Case is when the state called upon is a completed State.
	The return valuei is 0 for tie, 1 for a win or -1 for a loss (depending on minimax).
	
		in order to get the score from the substates, they must be created first...
		when the max score is returned, the corresponding choice has to be executed...somehow
		the solution would be to have an outer function that calls this...?
		When the score of the state is determined, it should be "complete"
	Else the function call is made for all substates.
	*/
	
	if (DEBUG){ printBoard(); }
	
	 // this would modify the value of score
	if (isComplete()){ // if its the base case: a leaf node, or if it has a score
		
		if (DEBUG){
			cout << "Base case has been invoked, as the above board is complete" << endl;
			cout << "Its score is " << score << endl;
		}	
		return score;
	}else{
		
		if (DEBUG){ cout << "Not the base case so" << endl; }
		createSubStates(); // creates the different possible sub states
		
		// create a scores list;
		List<int> scoresList;
		
		if (DEBUG){ cout << "using getScore on all the children, to make a list of scores" << endl; }
		
		State *current = children;
		
		current = current->next;
		
		while (current != NULL){
			
			scoresList.insertAtBack(current->getScore());
			current = current->next;
		}
		
		if (DEBUG){
		scoresList.print();
		cout << "depth is ?" << depth << endl;
		}
		
		if (depth%2 == 1){ // computer is 2, should return max...
			
			if (DEBUG){ cout << " choosing max " << scoresList.getMax() << endl;
			cout << " from : "; scoresList.print();
			}
			// choose max
			return scoresList.getMax();
		}else{
			if (DEBUG){ cout << "choosing min " << scoresList.getMin() << endl;
			cout << " from : "; scoresList.print();
			}
			
			return scoresList.getMin();
		}
	}
	
}


void State::placeMove(int x, int y){ // x indicates the row, y indicates the col

	// this is the one used by the algorithm
	
	
	// should also increase the depth counter of that state node
	// make sure the move is valid
	assert(x < 3 && x >= 0 && y < 3 && y >= 0);
	
	// make sure move is to an empty space
	if(board[x][y] == 0){
		
		if (depth%2 == 0){ // then it's the player 1s move
			
			
			if (DEBUG){ cout << "Player 1 moved to [" << x << ", " << y << "]" << endl; }
		
		// then it's player 1
			board[x][y] = 1;
			if (DEBUG){ cout << "Player 2's move" << endl;}
			
		}else{
			
			if (DEBUG){ cout << "Player 2 moved to [" << x << ", " << y << "]" << endl;}
		// its player 2
			board[x][y] = 2;
			if (DEBUG){ cout << "Player 1's move" << endl;}
		}
	
		
	}else{
		
		cout << "That space is already taken, please try a new spot." << endl;
		
	}
	
	depth++;
	printBoard();
}

void State::placeMove(State *ptr){ // this is used in the recursive function, basically copies another board

	for (int row = 0; row < 3; row ++){
		for (int col = 0; col < 3; col ++){
			board[row][col] = ptr->board[row][col];
		}
	}
	depth++;
	
	//printBoard();
}


void State::printBoard(){
	
	if (DEBUG){ cout << "PrintBoard() called, printing the board " << endl; }
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			cout << board[i][j];
		}
		cout << "\n";
	}
}
	
State* State::getChildrenHeader(){
	return children;
}

bool State::aWinner(){
	// this is used in the main function to test whether or not the game should continue
	// check diagnals
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0){

		cout << "Player " << board[0][0] << "is the winner" << endl;
		//score = (board[0][0] == 1? 1 : -1);
		return true;
		
	// check other diagnal	
	}else if (board[2][0] == board[1][1] && board[2][0] == board[0][2] && board[2][0] != 0){
	
		cout << "Player " << board[2][0] << " is the winner" << endl;
		//score = (board[2][0] == 1? 1 : -1);
		return true;
	
	// check rows and cols	
	}else{
	
		for (int i = 0; i < 3; i ++){
			
			// check rows
			if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != 0){
			
				// then there's a winner?		
				cout << "Player " << board[i][0] << " is the winner" << endl;
				//score = (board[i][0] == 1? 1 : -1);
				return true;
			
			// now check columns
			}else if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != 0){
			
				// then there's a winner
				cout << "Player " << board[0][i] << " is the winner" << endl;
				//score = (board[0][i] == 1? 1 : -1);
				return true;
			}		
		}
		
		if (depth == 9){
			// then this state must be a tie
			//score = 0;
			cout << "It's a tie" << endl;
			return true;
		}
	
		return false;
	}
}

bool State::aMove(){ // x indicates the row, y indicates the col
	
	// player moves
	int x, y;
	
	cin >> x >> y;
	
	// should also increase the depth counter of that state node
	// make sure the move is valid
	if (!(x < 3 && x >= 0 && y < 3 && y >= 0)){
		cout << "Invalid move, please try again" << endl;
		return false;
		
	}
	
	
	// make sure move is to an empty space
	if(board[x][y] == 0){
		
		if (depth%2 == 0){ // then it's the player 1s move
			
			cout << "Player 1 moved to [" << x << ", " << y << "]\n" << endl;
			
		// then it's player 1
			board[x][y] = 1;
			//cout << "Player 2's move" << endl;
			
		}else{
			cout << "Player 2 moved to [" << x << ", " << y << "]\n" << endl;
		// its player 2
			board[x][y] = 2;
			//cout << "Player 1's move" << endl;
		}
		
	}else{
		
		cout << "That space is already taken, please try a new spot." << endl;
		return false;
		//return false;
	}
	
	depth++;
	printBoard();
	return true;
}

void State::aMove(State *ptr){ // this is used in the recursive function, basically copies another board

	for (int row = 0; row < 3; row ++){
		for (int col = 0; col < 3; col ++){
			board[row][col] = ptr->board[row][col];
		}
	}
	depth++;
	
	cout << "Computer moved here" << endl;
	printBoard();
}
