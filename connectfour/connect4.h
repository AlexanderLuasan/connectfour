#pragma once
#include <string>
using namespace std;
#define boardx 7
#define boardy 7
#define numinrow 5
class connect4
{
public:
	connect4();//empty board
	connect4(char board[boardy][boardx],char turn);//board is a copy
	void move(int i);//attept move
	bool validmove(int i);//check if valid
	
	string tostring();//for printing
	char winner();//return winning side s for stalemate '#' for no one
	char turn();//retunrs turn

private:
	char player;
	char board[boardy][boardx];


};