#include "subject.h"
#include "card.h"
#include <vector>
using namespace std;

#ifndef TABLE_H
#define TABLE_H

class Table {

	// Cards currently on table in piles
	vector<Card> cards;

	public:

	// Constructor
	Table(vector<Card> cards);

	// Clears table
	void clear();

	// Checks if card put down is currently legal given other cards on table
	bool isLegal(Card c);

	// Checks if table is empty
	bool isEmpty();

	// Returns all the cards of the given suite currently on the table
	vector<Card> getSuiteCards(string s);

	// Adds a card to the table piles
	void addCard(Card c);

};

// Converts each integer to a rank
Card rankToInt(string suite);

#endif
