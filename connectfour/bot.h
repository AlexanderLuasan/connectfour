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
	bool iswinner;
	int losses;
	int bestmove;
	connect4 current;
	vector<tree> tolocation;
};

class bot
{
public:
	bot();
	int decide(connect4 board,char side);
private:

};