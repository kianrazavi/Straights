#include <random>
#include <chrono>
#include <memory>
#include <vector>
#include "card.h"
using namespace std;

#ifndef DECK_H
#define DECK_H

class Deck {

	vector<Card> cards;

	public:

	// Constructor
	Deck();

	// Returns cards in deck
	vector<Card> getCards();

	// Shuffles deck
	void shuffle(unsigned seed);


};

#endif
