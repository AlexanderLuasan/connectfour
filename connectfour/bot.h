#pragma once
#include "connect4.h"
#include <vector>

class tree
{
public:
	tree();//never used
	tree(connect4 board, int dep,char side);//recusive function trying all valid moves
	int decide();//uses the totals collected to find the best move
	void print(int dep);//print the tree in consul


private:
	int traps;
	bool valid;
	bool iswinner;
	int losses;
	int wins;
	
	int bestmove;
	connect4 current;
	vector<tree> tolocation;
};
tree build(connect4 board, int dep, char side);//simple threading
tree buildblank();
int fact(int i);//factorial function 

int decide(connect4 board,char side,int skill);//connecter for esay use by game