#include "view.h"
#include "human.h"
#include "player.h"
#include "table.h"
#include "deck.h"
#include "card.h"
#include <vector>
using namespace std;

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {

	bool newSeed = false;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	View *v;
	vector<shared_ptr<Player>> players;
	shared_ptr<Deck> deck;
	shared_ptr<Table> table;
	int maxScore = 80;
	int currPlayer;

	Card stringToCard(string s);


	public:

	// Constructor
	Controller(View *v);

	// Destructor
	~Controller();

	// Sets new random seed
	void setSeed(int s);

	// Starts a new game
	void startGame();

	// Starts a new round
	void newRound();

	// Plays a turn for the computer
	void computerTurn();

	// Plays a card for the human
	void humanPlay(string card);

	// Discards a card for the human
	void humanDiscard(string card);

	// Prints deck
	void deckPrint();

	// Detects if game is over
	bool isDone();

	// Detects player with lowest score and prints the winner
	void whoWins();

	// Gets view
	View* getView();

	// Gets table
	shared_ptr<Table> getTable();

	// Returns player whose turn it is
	shared_ptr<Player> whoseTurn();

	// Checks if given card string is valid
	bool valCard(string s);

	// Handles ragequit
	void rageQuit();

	// Resets round conditions
	void reset();

};

#endif
