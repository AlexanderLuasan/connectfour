#pragma once
#include <string>
using namespace std;
#define boardx 7
#define boardy 6
class connect4
{
public:
	connect4();
	connect4(char board[boardy][boardx]);
	void move(int i);
	bool validmove(int i);
	string tostring();
	char winner();
	char turn();

private:
	char board[boardy][boardx];


};