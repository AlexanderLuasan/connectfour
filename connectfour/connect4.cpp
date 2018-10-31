#include "connect4.h"

#include <iostream>
using namespace std;

connect4::connect4()
{
	for (int i = 0; i < boardy; i++) {
		for (int ii = 0; ii < boardx; ii++) {
			board[i][ii] = '#';
		}
	}
	player = 'x';
}

connect4::connect4(char board[boardy][boardx],char turn)
{
	for (int i = 0; i < 6; i++) {
		for (int ii = 0; ii < 7; ii++) {
			board[i][ii] = board[i][ii];
		}
	}
	player = turn;
}

void connect4::move(int col)
{

	for (int i = boardy-1; i > 0; i--) {
		board[i][col] = board[i-1][col];

	}
	board[0][col] = '#';
	board[0][col] = turn();
	if (player == 'x') {
		player = 'o';
	}
	else {
		player = 'x';
	}
}

bool connect4::validmove(int i)
{
	return (true);
}

string connect4::tostring()
{
	string end="";
	for (int i = 0; i <boardy ; i++) {
		for (int ii = 0; ii < boardx; ii++) {
			end += board[i][ii];
		}
		end += "\n";
	}
	return end;
}

char connect4::winner()//ways to win row col diagonal
{
	char inital;
	bool victory;
	
	for (int r = 0; r < boardy; r++) {
		for (int c = 0; c < boardx - numinrow+1; c++) {
			if (board[r][c] != '#') {
				inital = board[r][c];
				victory = true;
				for (int i = 0; i < numinrow; i++) {
					if (board[r][c + i] != inital) {
						victory = false;
						break;
					}
				}
				if (victory) {
					return inital;
				}
			}
		}
	}

	for (int c = 0; c < boardx; c++) {
		for(int r=0;r<boardy-numinrow+1;r++)
			if (board[r][c] != '#') {
				inital = board[r][c];
				victory = true;
				for (int i = 0; i < numinrow; i++) {
					if (board[r+i][c] != inital) {
						victory = false;
						break;
					}
				}
				if (victory) {
					return inital;
				}
			}
		
	}
	
	for (int r = 0; r < boardy-numinrow+1; r++) {
		for (int c = 0; c < boardx-numinrow+1; c++) {
			if (board[r][c] != '#') {
				inital = board[r][c];
				victory = true;
				for (int i = 0; i < numinrow; i++) {
					if (board[r + i][c + i] != inital) {
						victory = false;
						break;
					}
				}
				if (victory) {
					return inital;
				}
			}
			if (board[r][c + numinrow-1] != '#') {
				inital = board[r][c + numinrow-1];
				victory = true;
				for (int i = 0; i < numinrow; i++) {
					if (board[r + i][c + numinrow -1- i] != inital) {
						victory = false;
						break;
					}
					
				};
				if (victory) {
					return inital;
				}
			}
		}
	}
	bool stale = true;
	for (int i = 0; i < boardx; i++) {
		if (this->validmove(i) == true) {
			stale = false;
			break;
		}
	}
	if (stale) {
		return 's';
	}
	return '#';
}

char connect4::turn()
{


	return player;
}
