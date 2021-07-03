#include <iostream>
#include <ostream>
#include <string>
using namespace std;


#ifndef CARD_H
#define CARD_H

class Card {

	string rank;
	string suite;

	public:

	// Constructor
	Card(string rank, string suite);

	// Destructor
	~Card();

	// Gets rank of card 
	string getRank() const;

	// Gets suite of card
	string getSuite() const;

	// Converts rank to integer for score calculation and printing
	int rankToInt() const;

};

// Input card
istream &operator>>(istream &in, Card &card);

// Output card
ostream &operator<<(ostream &out, const Card &card);

// Equality operator
bool operator==(const Card &card1, const Card &card2);

// Inequality operator
bool operator!=(const Card &card1, const Card &card2);

#endif
