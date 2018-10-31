#pragma once
#include <string>
using namespace std;
#define boardx 7
#define boardy 7
#define numinrow 5
class connect4
{
public:
	connect4();
	connect4(char board[boardy][boardx],char turn);
	void move(int i);
	bool validmove(int i);
	
	string tostring();
	char winner();
	char turn();

private:
	char player;
	char board[boardy][boardx];


};