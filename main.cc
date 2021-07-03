#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "controller.h"
using namespace std;

int main(int argc, char * argv[]) {

	View *v;
	string cmd;
	string option;
	Controller ctr(v);

	// Deal with seed if given
	if (argc > 1) {
		ctr.setSeed(stoi(argv[1]));
	}

	// Start a game (initialize human/computer players)
	ctr.startGame();

	while (true) { // while games not done

		// Reset number of turns and start a new round
		int turns = 0;

		// Shuffle deck, deal cards and play first turn
		ctr.newRound();
		++turns;

		while (turns < 52) { // while round isn't over
			// Std computer turn
			if (ctr.whoseTurn()->getType() == "Computer") {

				ctr.computerTurn();
				++turns;

			}

			// Std human turn
			else {
				ctr.getView()->moveStatus(ctr.whoseTurn(), ctr.getTable());
				cout << ">";
				while (cin >> cmd) {

					if (cmd == "play") {
						cin >> option;
						try {						
							ctr.humanPlay(option);
							++turns;			
						} catch (Card c) {
							cout << "This is not a legal play" << endl;
						}
						break;
					}
					else if (cmd == "discard") {
						cin >> option;
						try {
							ctr.humanDiscard(option);
							++turns;

						} catch (Card c) {
							cout << "You have a legal play. You may not discard." << endl;
						}
						break;				
					}
					else if (cmd == "deck") {
						ctr.deckPrint();
					}
					else if (cmd == "quit") {
						return 0;
					}
					else if (cmd == "ragequit") {
						ctr.rageQuit();
						break;
					}
					else {
						cerr << "Invalid command: \"" << cmd << "\"" <<  endl;
						cout << ">";
					}

				}


			} 



		}
		if (ctr.isDone()) {
			ctr.whoWins();
			break;
		} 

		else {			
			ctr.reset();
		}

	}
}
