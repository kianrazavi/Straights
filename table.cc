#include "table.h"
#include "subject.h"
#include "card.h"
#include <algorithm>
#include <vector>
using namespace std;

// Constructor
Table::Table(vector<Card> cards)
	: cards{cards}
{}

// Clears table
void Table::clear() {
	cards.clear();
}

// Converts int to corresponding card of given suite
Card intToRank(int i, string suite) {

	string s;

	if (i == 1) {
		s = "A";
	}
	else if (i == 10) {
		s = "T";
	}
	else if (i == 11) {
		s = "J";
	}
	else if (i == 12) {
		s = "Q";
	}
	else if (i == 13) {
		s = "K";
	}
	else {
		s = to_string(i);
	}

	Card c = Card(s, suite);
	return c;
}

// Checks if card put down is currently legal to play
bool Table::isLegal(Card c) {

	int tableLength = cards.size();

	for (int i = 0; i < tableLength; ++i) {
		if (cards[i] == c) {
			return false;
		}
	}

	if (c.getRank() == "7") {
		return true;
	}

	for (int i = 0; i < tableLength; ++i) {
		if (cards[i].getSuite() == c.getSuite()) {
			if ((cards[i].rankToInt() == c.rankToInt() - 1) || (cards[i].rankToInt() == c.rankToInt() +1)) {
				return true;
			}
		}
	}
	return false;
}

// Checks if table is empty
bool Table::isEmpty() {
	return cards.size() == 0;
}

// Returns all the cards of given suite currently on table
vector<Card> Table::getSuiteCards(string s) {

	vector<int> v;
	vector<Card> v1;
	int tableLength = cards.size();
	for (int i = 0; i < tableLength; ++i) {

		if (cards[i].getSuite() == s) {
			v.push_back(cards[i].rankToInt());
			sort(v.begin(), v.end());
		}
	}

	int vSize = v.size();

	for (int i = 0; i < vSize; ++i) {
		v1.emplace_back(intToRank(v[i], s));
	}
	return v1;
}

// Adds card to table piles
void Table::addCard(Card c) {
	cards.emplace_back(c);
}
