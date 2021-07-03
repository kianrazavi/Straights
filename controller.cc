#include "view.h"
#include "human.h"
#include "computer.h"
#include "controller.h"
#include "player.h"
#include "table.h"
#include "card.h"
#include "deck.h"
#include <vector>
#include <ctype.h>
#include <iostream>
#include <string>
using namespace std;

// Checks if given card string is valid
bool Controller::valCard(string s) {
	if ((isdigit(s[0]) || s[0] == 'A' || s[0] == 'T' || s[0] == 'J' || s[0] == 'Q' || s[0] == 'K')
			&& (s[1] == 'S' || s[1] == 'H' || s[1] == 'C' || s[1] == 'D')) {
		return true;
	}

	cout << "This is not a legal play" << endl; 
	return false;
}

// Converts string to card
Card Controller::stringToCard(string s) {
	string rank;
	string suite;
	rank += s[0];
	suite += s[1];

	Card c = Card(rank, suite);
	return c;

}

// Constructor
Controller::Controller(View *v)
	: v{v}
{
	deck = make_shared<Deck>();


} 

// Destructor
Controller::~Controller() {  // delete players?

}

// Sets seed if given
void Controller::setSeed(int s) {
	seed = s;
}


// Starts a new game (initializes players)
void Controller::startGame() {

	vector<Card> temp;

	table = make_shared<Table>(temp);

	vector<string> playerStats = v->playerDecide();

	for (int i = 0; i < 4; ++i) {

		if (playerStats[i] == "h") {
			players.emplace_back(make_shared<Human>(i + 1, table));

		}

		if (playerStats[i] == "c") {
			players.emplace_back(make_shared<Computer>(i + 1, table));
		}

	}

}

// Starts a new round (shuffles deck and deals cards)
void Controller::newRound() {

	// Shuffle deck
	deck->shuffle(seed);

	// Deal cards to each player (first 13 to P1, etc.)
	for (int i = 0; i < 13; ++i) {
		players[0]->addCard(deck->getCards()[i]);
	}

	for (int i = 13; i < 26; ++i) {
		players[1]->addCard(deck->getCards()[i]);
	}

	for (int i = 26; i < 39; ++i) {
		players[2]->addCard(deck->getCards()[i]);
	}

	for (int i = 39; i < 52; ++i) {
		players[3]->addCard(deck->getCards()[i]);
	}

	shared_ptr<Player> firstPlayer;
	// Find player with 7 of spades
	for (int i = 0; i < 4; ++i) {
		if (players[i]->has7S()) {
			v->firstMoveStatus(players[i]);
			firstPlayer = players[i];		
		}
	}
	currPlayer = firstPlayer->getID();

	// If human, use "play" cmd with 7S
	if (firstPlayer->getType() == "Human") {

		v->moveStatus(firstPlayer, table);
		while (true) {
			cout << ">";
			string cmd;
			string option;
			cin >> cmd;
			if (cmd == "play") {
				cin >> option;

				if (valCard(option)) {
					try {
						firstPlayer->playCard(stringToCard(option));
						break;
					} catch (Card c) {
						cout << "This is not a legal play." << endl;
					}
				}			}
			else if (cmd == "deck") {
				v->printDeck(deck);
			}
			else if (cmd == "discard") {
				cin >> option;
				cout << "You have a legal play. You may not discard." << endl;
			}
			else if (cmd == "quit") {
				return;
			}
			else if (cmd == "ragequit") {
				rageQuit();
				firstPlayer = players[currPlayer - 1];
				break;
			}
			else {
				cout << "Invalid command: \"" << cmd << "\"" <<  endl;
			}
		}
	}
	// If computer, play 7S
	if (firstPlayer->getType() == "Computer")  {
		string move = firstPlayer->moveLogic();
		firstPlayer->compMove(move); 

	}

	if (currPlayer == 4) {
		currPlayer = 1;
	}
	else {
		++currPlayer;
	}
}

// Plays a computer turn
void Controller::computerTurn() {

	shared_ptr<Player> playerNow = players[currPlayer - 1];

	string move = playerNow->moveLogic();
	playerNow->compMove(move);

	if (currPlayer == 4) {
		currPlayer = 1;
	}
	else {
		++currPlayer;
	}
}

// Plays a card for human
void Controller::humanPlay(string card) {


	shared_ptr<Player> playerNow = players[currPlayer - 1];
	if (valCard(card)) {
		try {
			playerNow->playCard(stringToCard(card));
			if (currPlayer == 4) {
				currPlayer = 1;
			}
			else {
				++currPlayer;
			}
		} catch (Card c) {
			throw;
		}
	}

}

// Discards a card for human
void Controller::humanDiscard(string card) {

	shared_ptr<Player> playerNow = players[currPlayer - 1];
	if (valCard(card)) {
		try {
			playerNow->discard(stringToCard(card));
			if (currPlayer == 4) {
				currPlayer = 1;
			}
			else {
				++currPlayer;
			}	

		} catch (Card c) {
			throw;
		}
	}
}

// Prints current deck for human as per cmd
void Controller::deckPrint() {
	v->printDeck(deck);
	cout << ">";
}

// Detects if game is over after round ends
bool Controller::isDone() {

	for (int i = 0; i < 4; ++i) {
		players[i]->getCurrScore();
		int finalScore = players[i]->calcFinalScore();
		if (finalScore >= 80) {
			return true;
		}
	}
	return false;
}

// Detects player with lowest score and deems them the winner
void Controller::whoWins() {

	v->endOfRound(players);

	int min = 1000;
	shared_ptr<Player> p;

	for (int i = 0; i < 4; ++i) {
		if (players[i]->calcFinalScore() < min) {
			min = players[i]->calcFinalScore();
			p = players[i];
		}
	}

	v->printWinner(p);

}

// Returns player whose turn it is
shared_ptr<Player> Controller::whoseTurn() {
	return players[currPlayer - 1];
}


// Gets view
View* Controller::getView() {
	return v;
}

// Gets table
shared_ptr<Table> Controller::getTable() {
	return table;
}

// Handles ragequit
void Controller::rageQuit() {

	shared_ptr<Player> playerNow = players[currPlayer - 1];

	int playerNowID = playerNow->getID();
	int playerNowTotalScore = playerNow->getTotalScore();
	vector<Card> playerNowCurrCards = playerNow->getCurrCards();
	vector<Card> playerNowDiscards = playerNow->listDiscard();

	int currIndex = currPlayer - 1;
	players.erase(players.begin() + currIndex);

	players.insert(players.begin() + currIndex, make_shared<Computer>(playerNowID, table));

	playerNow = players[currPlayer - 1];
	playerNow->setCurrCards(playerNowCurrCards);
	playerNow->setDiscards(playerNowDiscards);
	playerNow->setTotalScore(playerNowTotalScore);	
	cout << "Player" << playerNowID << " ragequits. A computer will now take over." << endl;
}

// Resets round conditions (clears player hands)
void Controller::reset() {
	v->endOfRound(players);
	for (int i = 0; i < 4; ++i) {
		players[i]->reset();
		players[i]->clearCards();
		table->clear();
	}
}






