#include "view.h"
#include "card.h"
#include "table.h"
#include "deck.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Constructor
View::View() {};

// Asks if player is human or computer
vector<string> View::playerDecide() {

	vector<string> s;

	for (int i = 1; i < 5; ++i) {
		cout << "Is Player" << i << " a human (h) or a computer (c)?" << endl;
		string type;
		cin >> type;
		s.emplace_back(type);
	}
	return s;
}

// Prints table/hand status for player making move
void View::moveStatus(shared_ptr<Player> p, shared_ptr<Table> t) {
	cout << "Cards on the table:" << endl;

	int clubSize = t->getSuiteCards("C").size();
	int diamondSize = t->getSuiteCards("D").size();
	int heartSize = t->getSuiteCards("H").size();
	int spadeSize = t->getSuiteCards("S").size();
	int handSize = p->getCurrCards().size();
	int legalSize = p->listLegal().size();

	cout << "Clubs: ";
	for (int i = 0; i < clubSize; ++i) {
		cout << t->getSuiteCards("C")[i].getRank() << " ";
	}
	cout << endl;

	cout << "Diamonds: ";
	for (int i = 0; i < diamondSize; ++i) {
		cout << t->getSuiteCards("D")[i].getRank() << " ";
	}
	cout << endl;

	cout << "Hearts: ";
	for (int i = 0; i < heartSize; ++i) {
		cout << t->getSuiteCards("H")[i].getRank() << " ";
	}
	cout << endl;

	cout << "Spades: ";
	for (int i = 0; i < spadeSize; ++i) {
		cout << t->getSuiteCards("S")[i].getRank() << " ";
	}
	cout << endl;

	cout << "Your hand: ";
	for (int i = 0; i < handSize; ++i) {
		cout << p->getCurrCards()[i] << " ";
	}
	cout << endl;

	cout << "Legal plays: ";
	for (int i = 0; i < legalSize; ++i) {
		cout << p->listLegal()[i] << " ";
	}
	cout << endl;

}

// Prints the table/hand status for the first turn of the round
void View::firstMoveStatus(shared_ptr<Player> p) {
	cout << "A new round begins. It's Player" << p->getID() << "'s turn to play." << endl;
}

// Prints deck
void View::printDeck(shared_ptr<Deck> d) {

	int counter = 0;
	int deckSize = d->getCards().size();

	for (int i = 0; i < deckSize; ++i) {

		cout << d->getCards()[i];
		++counter;

		if (counter % 13 == 0) {
			cout << endl;
			continue;
		}
		cout << " ";
	}
}

// Prints ragequit message
void View::printRQ(Player &p) {
	cout << "Player" << p.getID() << " ragequits. A computer will now take over." << endl;
} 

// Prints score calculations
void View::endOfRound(vector<shared_ptr<Player>> players) {

	int playerSize = players.size();

	for (int i = 0; i < playerSize; ++i) {

		cout << "Player" << players[i]->getID() << "'s discards: ";

		int discardSize = players[i]->listDiscard().size();

		for (int j = 0; j < discardSize; ++j) {
			cout << players[i]->listDiscard()[j];

			if (j == discardSize - 1) {
				break;
			}
			cout << " ";
		}
		cout << endl;

		cout << "Player" << players[i]->getID() << "'s score: " << players[i]->getTotalScore() << " + " <<  players[i]->getCurrScore() << " = " <<  players[i]->calcFinalScore();
		cout << endl;
	}

}

// Prints winner
void View::printWinner(shared_ptr<Player> p) {
	cout << "Player" << p->getID() << " wins!" << endl;

}
