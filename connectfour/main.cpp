#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <future>
#include <thread>
#include "connect4.h";
#include "bot.h"
using namespace std;

const int radius = 50;
const int arrowsize = 40;
int main() {
	srand(time(NULL));
	cout << "connect five" << endl;

	al_init();
	al_init_primitives_addon();

	ALLEGRO_DISPLAY * screen=nullptr;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER * timer;

	al_install_keyboard();


	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 20.0);



	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());


	bool gameing = true;
	while (gameing) {
		connect4 game = connect4();
		//game vars
		int botskill=5;
		bool playerTurn = true;
		char botside;
		char playerside;
		//drawing things
		int playerpos = 0;
		int botpos = 0;
		int waitingtime = 0;
		int dest = -1;
		//loops
		bool options = true;
		bool running = true;
		

		
		bool menu = true;
		while (menu) {//menu
			int choiceint;
			cout << "1:start" << endl;
			cout << "2:rules" << endl;
			cout << "3:options" << endl;
			cout << "4:exit" << endl;
			cin >> choiceint;
			switch (choiceint) {
			case 1:
				menu = false;
				break;
			case 2:
				cout << "player take turns adding their pieces to the board." << endl;
				cout << "the pieces are added to the top and push other peices on the board down." << endl;
				cout << "pieces can not be pushed of the board" << endl;
				cout << "the game ends when one player gets " << numinrow << " in a row." << endl;
				cout << "use the arrow keys to move and enter to select" << endl;
				break;

			case 3:
				options = true;
				while (options)//edit ooptions
				{
					cout << "1:playerstarts=" << playerTurn << endl;
					cout << "2:botskill=" << botskill << endl;
					cout << "3:exit" << endl;
					cin >> choiceint;
					switch (choiceint) {
					case 1:
						playerTurn = !playerTurn;
						break;
					case 2:
						cout << "high bot skill make incress thinking time" << endl;
						cout << "enter botskill: ";
						int ch;
						cin >> ch;
						botskill = ch;
						break;
					case 3:
						options = false;
						break;
					default:
						break;
					}

				}
				break;
			case 4:
				running = false;
				gameing = false;
				menu = false;
				break;
			default:
				cout << "enter a valid option!" << endl;
			}
			

		}

		//side declation
		if (playerTurn) {
			botside = 'o';
			playerside = 'x';
		}
		else {
			botside = 'x';
			playerside = 'o';
		}
		//start visual
		
		future<int> m;
		if (running) {
			al_start_timer(timer);
			screen = al_create_display(radius * 2 * boardx, radius * 2 * boardy + 40);
			al_register_event_source(queue, al_get_display_event_source(screen));
			if (!playerTurn) {
				m = async(&decide, game, botside, botskill);
			}
		}
		while (running) {
			ALLEGRO_EVENT event;

			al_wait_for_event(queue, &event);

			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
			}
			else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
					if (playerpos > 0) {
						playerpos -= 1;
					}

				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
					if (playerpos < boardx - 1) {
						playerpos += 1;
					}
				}
				else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
					if (playerTurn&&game.validmove(playerpos)) {
						game.move(playerpos);
						playerTurn = false;
						if (game.winner() == '#') {
							m = async(&decide, game, botside, botskill);
						}
						else {
						}
						
					}
				}
			}
			else if (event.type == ALLEGRO_EVENT_TIMER) {
				//game functions
				if (game.winner() != '#') {
					running = false;
				}else if (playerTurn == false) {
					waitingtime += 1;
					if (dest == -1) {
						auto status = m.wait_for(0ms);
						if (status == future_status::ready) {
							dest = m.get();
							cout << dest << endl;
						}
					}
					
					if (waitingtime > 30 && dest != -1) {

						if (dest == botpos) {
							game.move(dest);
							playerTurn = true;
							waitingtime = 0;
							dest = -1;
						}
						else if (waitingtime % 5 == 0) {
							if (botpos < dest) {
								botpos += 1;
							}
							else if (botpos > dest) {
								botpos -= 1;
							}
						}
					}
					else if (waitingtime % 7 == 0) {
						if (rand() % 2) {
							botpos += 1;
							if (botpos >= boardx) {
								botpos = boardx - 1;
							}
						}
						else {
							botpos -= 1;
							if (botpos < 0) {
								botpos = 0;
							}
						}
					}
				}


				//drawing
				int layer = 0;
				int pos = 0;
				string gameinfo = game.tostring();
				al_clear_to_color(al_map_rgb(255, 255, 255));
				for (int i = 0; i < gameinfo.length(); i++) {
					if (gameinfo[i] == botside) {
						al_draw_circle(2 * radius * pos + radius, 2 * radius * layer + radius + arrowsize, radius-2, al_map_rgb(255, 0, 0), 2.0);
					}
					else if (gameinfo[i] == playerside) {
						al_draw_circle(2 * radius * pos + radius, 2 * radius * layer + radius + arrowsize, radius-2, al_map_rgb(0, 0, 255), 2.0);
					}
					else if (gameinfo[i] == '\n') {
						layer += 1;
						pos = -1;
					}
					pos += 1;
				}
				//draw arrow
				al_draw_line(playerpos * 2 * radius+(playerTurn*10), 0, playerpos * 2 * radius + 2 * radius- (playerTurn * 10), 0, al_map_rgb(0, 0, 255), 5.0);
				al_draw_line(playerpos * 2 * radius+ (playerTurn * 10), 0, playerpos * 2 * radius + radius, arrowsize, al_map_rgb(0, 0, 255), 5.0);
				al_draw_line(playerpos * 2 * radius + radius, arrowsize, playerpos * 2 * radius + 2 * radius- (playerTurn * 10), 0, al_map_rgb(0, 0, 255), 5.0);

				al_draw_line(botpos * 2 * radius + (!playerTurn * 10), 0, botpos * 2 * radius + 2 * radius - (!playerTurn * 10), 0, al_map_rgb(255, 0, 0), 5.0);
				al_draw_line(botpos * 2 * radius + (!playerTurn * 10), 0, botpos * 2 * radius + radius, arrowsize, al_map_rgb(255, 0, 0), 5.0);
				al_draw_line(botpos * 2 * radius + radius, arrowsize, botpos * 2 * radius + 2 * radius - (!playerTurn * 10), 0, al_map_rgb(255, 0, 0), 5.0);

				al_flip_display();
			}

		}
		
		if (gameing == true) {
			if (game.winner() == '#') {
				gameing = false;
				break;
			}
			cout << game.tostring() << endl;
			cout << "the winner is ";
			if (game.winner() == botside) {
				cout << "red";
			}
			else if (game.winner() == 's') {
				cout << "no one";
			}
			else {
				cout << "blue";
			}
			cout << endl;
			cout << "would you like to play again? y/(n)" << endl;
			char choice;
			cin >> choice;
			if (screen != nullptr) {
				al_destroy_display(screen);
			}
			if (choice == 'y') {
				gameing = true;
			}
			else {
				gameing = false;
			}
		}
	}

	return 0;
}