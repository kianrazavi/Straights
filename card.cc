#include <iostream>
#include <string>
#include <ostream>
#include "card.h"
using namespace std;

// Constructor
Card::Card(string rank, string suite)
	: rank{rank}, suite{suite}
{}

// Destructor
Card::~Card() {}

// Gets rank of card
string Card::getRank() const {
	return rank;
}

// Gets suite of card
string Card::getSuite() const {
	return suite;
}

// Converts rank to corresponding integer
int Card::rankToInt() const {
	if (rank == "A") {
		return 1;
	}
	else if (rank == "T") {
		return 10;
	}
	else if (rank == "J") {
		return 11;
	}
	else if (rank == "Q") {
		return 12;
	} 
	else if (rank == "K") {
		return 13;
	}

	else {

		return stoi(rank);
	}
}


// Input card
istream &operator>>(istream &in, Card &card) { // might not need
}

// Output card as "rank""suite"
ostream &operator<<(ostream &out, const Card &card) {
	out << card.getRank() << card.getSuite();	
	return out;
}

// Equality operator, returns true if two cards are equal
bool operator==(const Card &card1, const Card &card2) {
	return ((card1.getRank() == card2.getRank()) && (card1.getSuite() == card2.getSuite()));
}

// Inequality operator, returns true if two cards are not equal
bool operator!=(const Card &card1, const Card &card2) {
	return ((card1.getRank() != card2.getRank()) && (card1.getSuite() == card2.getSuite()));
}
