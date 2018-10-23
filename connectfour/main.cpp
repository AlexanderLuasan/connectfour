#include <iostream>
#include "connect4.h";
#include "bot.h"
using namespace std;

int main() {
	cout << "connect four" << endl;
	
	connect4 game = connect4();
	//tree(game,2, 'x').print(0);
	//system("pause");
	cout << game.tostring() << endl;
	bot a = bot();
	while (game.winner() == '#') {
		game.move(a.decide(game,'x'));
		cout << game.tostring() << endl;
		int c;
		cin >> c;
		game.move(c);
	}


	system("pause");
	return 0;
}