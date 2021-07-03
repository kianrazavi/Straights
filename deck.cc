#include <chrono>
#include <algorithm>
#include <memory>
#include <vector>
#include <random>
#include "deck.h"
#include "card.h"
using namespace std;

string r[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
string s[4] = {"C", "D", "H", "S"};

// Constructor
Deck::Deck() {

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {

			Card newCard = Card(r[j], s[i]);
			cards.push_back(newCard);

		}
	}

}

// Returns cards in current deck
vector<Card> Deck::getCards() {
	return cards;
}

// Shuffles deck
void Deck::shuffle(unsigned seed) {

	default_random_engine rng{seed};

	for (int i = 0; i < 1000; i++) {
		std::shuffle(cards.begin(), cards.end(), rng);
	}
}

