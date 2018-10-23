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
}

connect4::connect4(char board[boardy][boardx])
{
	for (int i = 0; i < 6; i++) {
		for (int ii = 0; ii < 7; ii++) {
			board[i][ii] = board[i][ii];
		}
	}
}

void connect4::move(int col)
{
	int xcount=0;
	int ocount=0;
	for (int i = 0; i < boardy; i++) {
		for (int ii = 0; ii < boardx; ii++) {
			if (board[i][ii] == 'x') {
				xcount += 1;
			}
			else if(board[i][ii]=='o') {
				ocount += 1;
			}
		}
	}


	for (int i = 0; i < boardy; i++) {
		if (board[i][col] == '#') {
			if (xcount > ocount) {
				board[i][col] ='o';
			}
			else {
				board[i][col] = 'x';
			}
			break;
		}
	}
}

bool connect4::validmove(int i)
{
	return (board[boardy-1][i]=='#');
}

string connect4::tostring()
{
	string end="";
	for (int i = boardy-1; i >-1 ; i--) {
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
		for (int c = 0; c < boardx-3; c++) {
			if (board[r][c] != '#') {
				inital = board[r][c];
				victory=true;
				for (int i = 0; i < 4; i++) {
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
		for (int r = 0; r < boardy-3; r++) {
			if (board[r][c] != '#') {
				inital = board[r][c];
				victory = true;
				for (int i = 0; i < 4; i++) {
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
	}

	for (int c = 0; c < boardx - 3; c++) {
		for (int r = 0; r< boardy - 3; r++) {
			if (board[r][c] != '#') {
				inital = board[r][c];
				victory = true;
				for (int i = 0; i < 4; i++) {
					if (board[r + i][c + i] != inital) {
						victory = false;
						break;
					}
				}
				if (victory) {
					return inital;
				}
			}
			if (board[r][c+3] != '#') {
				inital = board[r][c+3];
				victory = true;
				for (int i = 0; i < 4; i++) {

					if (board[r + i][c - i] != inital) {
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
	return '#';
}

char connect4::turn()
{
	int xcount = 0;
	int ocount = 0;
	for (int i = 0; i < boardy; i++) {
		for (int ii = 0; ii < boardx; ii++) {
			if (board[i][ii] == 'x') {
				xcount += 1;
			}
			else if (board[i][ii] == 'o') {
				ocount += 1;
			}
		}
	}

	if (xcount > ocount) {
		return 'o';
	}
	else {
		return 'x';
	}
}
