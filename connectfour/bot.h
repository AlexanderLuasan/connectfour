#pragma once
#include "connect4.h"
#include <vector>

class tree
{
public:
	tree();
	tree(connect4 board, int dep,char side);
	int decide();
	void print(int dep);


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
tree build(connect4 board, int dep, char side);
tree buildblank();
int fact(int i);

int decide(connect4 board,char side,int skill);