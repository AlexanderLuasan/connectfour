#include "bot.h"
#include <iostream>
#include <random>
using namespace std;
tree::tree()
{
	bestmove = -2;
	iswinner = false;
	losses = 0;
}

tree::tree(connect4 board, int dep,char side)
{
	bestmove = -1;
	iswinner = false;
	losses = 0;
	current = board;
	if (current.winner() == '#') {
		if (dep >0) {
			if (current.turn() == side) {
				for (int i = 0; i < boardx; i++) {
					if (current.validmove(i)) {
						connect4 temp2 = current;
						temp2.move(i);
						tree temp = tree(temp2, dep - 1, side);
						tolocation.push_back(temp);
						losses += temp.losses;
					}
					else {
						tree temp = tree();
						tolocation.push_back(temp);
					}

					if (tolocation[i].iswinner==true) {
						iswinner = true;
						bestmove = i;
						losses = 0;
					}
				}
			}
			else {
				for (int i = 0; i < boardx; i++) {

					if (current.validmove(i)) {
						connect4 temp2 = current;
						temp2.move(i);
						tree temp = tree(temp2, dep - 1, side);
						tolocation.push_back(temp);
						losses = tolocation[i].losses;
					}
					else {
						tree temp = tree();
						tolocation.push_back(temp);
					}
				}
				if (tolocation.size() > 0) {
					iswinner = true;
					for (int i = 0; i < tolocation.size(); i++) {
						if (tolocation[i].iswinner==false) {
							iswinner = false;
							break;
						}
					}
					for (int i = 0; i < tolocation.size(); i++) {
						losses += tolocation[i].losses;
					}
				}
	
			}
		}
	}
	else if(current.winner() == side) {
		iswinner = true;
	}
	else {
		losses += 1;
	}
}

int tree::decide()
{
	if (bestmove == -1) {
		int possiblemoves[boardx];
		int pos=0;
		for (int i = 0; i < tolocation.size(); i++) {
			if (tolocation[i].losses == 0) {
				possiblemoves[pos] = i;
				pos += 1;
			}
		}
		if (pos == 1) {
			cout << "counterplay" << endl;
			return possiblemoves[0];
		}
		if (pos > 0) {
			cout << "ties" << endl;
			return possiblemoves[rand() % pos];
		}
		
		else {
			int minpos = 0;
			for (int i = 0; i < tolocation.size(); i++) {
				if (tolocation[i].losses < tolocation[minpos].losses) {
					minpos = i;
				}
			}
			cout << "minlose" << endl;
			return minpos;
		}
		
	}
	else {
		cout << "bestmove" << endl;
		return bestmove;
	}
}

void tree::print(int dep)
{
	for (int i = 0; i < tolocation.size();i++) {
		for (int l = 0; l < dep; l++) {
			cout << "\t";
		}
		cout << i << " ";
		cout << tolocation[i].iswinner << " ";
		cout << tolocation[i].losses;
		cout << endl;
		tolocation[i].print(dep+1);
	}
}

bot::bot()
{
}

int bot::decide(connect4 board, char side)
{
	tree decision(board, 5, side);
	//decision.print(0);
	return decision.decide();

}
