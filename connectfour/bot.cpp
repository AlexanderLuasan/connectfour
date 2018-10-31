#include "bot.h"
#include <iostream>
#include <random>
#include <future>
#include <thread>
using namespace std;
tree::tree()
{
	bestmove = -2;
	iswinner = false;
	losses = 0;
	valid = false;
	wins = 0;
}
tree build(connect4 board, int dep, char side)
{
	return tree(board,dep,side);
}
tree buildblank()
{
	return tree();
}
int fact(int n) {
	int	end = 1;
	for (int i = 2; i < n+1; i++) {
		end *= i;
	}
	return end;
}


tree::tree(connect4 board, int dep,char side)
{
	valid = true;
	bestmove = -1;
	iswinner = false;
	traps = 0;
	losses = 0;
	wins = 0;
	current = board;
	if (current.winner() == '#') {
		if (dep >0) {
			if (current.turn() == side) {
				for (int i = 0; i < boardx; i++) {
					if (current.validmove(i)) {
						connect4 temp2 = current;
						temp2.move(i);
						tolocation.push_back(tree(temp2, dep - 1, side));
						losses += tolocation[i].losses;
						wins += tolocation[i].wins;
						traps += tolocation[i].traps;
					}
					else {
						tolocation.push_back(tree());
					}


					if (tolocation[i].iswinner==true) {
						iswinner = true;
						bestmove = i;
						losses = 0;
						for (int ii = i + 1; ii < boardx; ii++) {
							tolocation.push_back(tree());
						}
						for (int ii = 0; ii < i; ii++) {
							tolocation[ii] = tree();
						}
						break;
					}
				}
			}
			else {
				bool nonzero = false;

				future<tree> branches[boardx];
				for (int i = 0; i < boardx; i++) {

					if (current.validmove(i)) {
						nonzero = true;
						connect4 temp2 = current;
						temp2.move(i);
						branches[i] = async(&build, temp2, dep - 1, side);

						//tolocation.push_back(tree(temp2, dep - 1, side));
						
					}
					else {
						branches[i] = async(&buildblank);
						//tolocation.push_back(tree());
					}
				}
				for (int i = 0; i < boardx; i++) {
					tolocation.push_back(branches[i].get());
					losses += tolocation[i].losses;
					wins += tolocation[i].wins;
					traps += tolocation[i].iswinner;
				}

				if (nonzero) {
					iswinner = true;
					for (int i = 0; i < boardx; i++) {
						if (tolocation[i].iswinner==false&& tolocation[i].valid) {
							iswinner = false;
							break;
						}
					}
					for (int i = 0; i <boardx; i++) {
						losses += tolocation[i].losses;
					}
				}
	
			}
		}
	}
	else if(current.winner() == side) {
		iswinner = true;
		wins = 1 * fact(dep+1);
	}
	else {
		losses = 1*fact(dep+1);//add factorial
	}
}

int tree::decide()
{
	cout << "valids: ";
	for (int i = 0; i < boardx; i++) {
		if (tolocation[i].valid) {
			cout << i << " ";
		}
	}
	cout << endl;
	if (bestmove == -1) {
		int possiblemoves[boardx];
		int pos=0;
		for (int i = 0; i < boardx; i++) {
			if (tolocation[i].losses == 0 && tolocation[i].valid) {
				possiblemoves[pos] = i;
				pos += 1;
			}
		}
		if (pos == 1) {
			cout << "counterplay" << endl;
			return possiblemoves[0];
		}
		if (pos > 0) {
			int besttraps = possiblemoves[0];
			for (int ii = 0; ii < pos; ii++) {
				if (tolocation[besttraps].wins < tolocation[possiblemoves[ii]].wins) {
					besttraps = possiblemoves[ii];
				}
				else if (tolocation[besttraps].wins == tolocation[possiblemoves[ii]].wins) {
					if (rand() % 2) {
						besttraps = possiblemoves[ii];
					}
				}
			}
			if (tolocation[besttraps].traps>0) {
				cout << "moving to trap" << endl;
				return besttraps;
			}
			int bestwins = possiblemoves[0];
			for (int ii = 0; ii < pos; ii++) {
				if (tolocation[bestwins].wins < tolocation[possiblemoves[ii]].wins) {
					bestwins = possiblemoves[ii];
				}
				else if (tolocation[bestwins].wins == tolocation[possiblemoves[ii]].wins) {
					if (rand() % 2) {
						bestwins = possiblemoves[ii];
					}
				}
			}
			if (tolocation[bestwins].wins>0) {
				cout << "moving to win" << endl;
				return bestwins;
			}
			else {
				cout << "ties" << endl;
				return possiblemoves[rand() % pos];
			}
		}
		else {
			int minpos = 0;
			for (int i = 0; i < boardx; i++) {
				if (tolocation[i].losses < tolocation[minpos].losses&&tolocation[i].valid) {
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
		cout << "trap?: " <<tolocation[i].iswinner << " ";
		cout << "trapout: " << tolocation[i].traps << " ";
		cout << "numOfLose: " <<tolocation[i].losses << " ";
		cout << "numOfWins: " <<tolocation[i].wins << " ";
		cout << endl;
		if (dep<1&& tolocation[i].traps>0) {
			tolocation[i].print(dep + 1);
		}
	}
}



int decide(connect4 board, char side,int skill)
{
	tree decision(board, skill, side);
	decision.print(0);
	return decision.decide();

}
