#ifndef STATE_H
#define STATE_H

class State{ // basically a node
	public:
		State(int [3][3]); // give it a constructor later...
		State();
		~State();
		int getScore();
		void placeMove(int, int);
		void placeMove(State *);
		void printBoard();
		bool isComplete();
		void createSubStates();
		void decide();
		State *getChildrenHeader();
		State *children; // this is the header to the linked list of children nodes
		State *next; // header to the linked list of sibling states 
		bool aWinner(); // used in game, because of couts
		bool aMove(); // used in game
		void aMove(State *);
		int getDepth() { return depth;}
		
	private:
		
		int depth; // ranges from 0 to 9, indicates the number of turns
		//int depth; // ranges from 0 to 8, indicates the number of turns
		int board[3][3];
		int score;
	
};

#endif
