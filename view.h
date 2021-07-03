#include "player.h"
#include "card.h"
#include "table.h"
#include "deck.h"
#include <vector>
#include <string>
using namespace std;

#ifndef VIEW_H
#define VIEW_H

class View {

	public:

		// Constructor
		View();

		// Asks if player is human or computer
		vector<string> playerDecide();

		// Prints table/hand status for player making move
		void moveStatus(shared_ptr<Player> p, shared_ptr<Table> t);

		// Prints the table/hand status for the first player making move
		void firstMoveStatus(shared_ptr<Player> p);

		// Prints deck as per "deck" command
		void printDeck(shared_ptr<Deck> d);

		// Prints ragequit message
		void printRQ(Player &p);

		// Prints score calculations
		void endOfRound(vector<shared_ptr<Player>> players);

		// Prints winner
		void printWinner(shared_ptr<Player> p);

};

#endif
