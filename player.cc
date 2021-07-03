#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "card.h"
#include "player.h"
using namespace std;

// Constructor
Player::Player(int ID, shared_ptr<Table> t)
	: ID{ID}, t{t}
{}

// Put down a card (removes from current hand)
void Player::playCard(Card c) {

	if (t->isLegal(c) && (find(listLegal().begin(), listLegal().end(), c) != listLegal().end())) {	
		currCards.erase(remove(currCards.begin(), currCards.end(), c), currCards.end());
		t->addCard(c);
		cout << "Player" << ID << " plays " << c << "." << endl;
	}
	else {
		throw Card(c);
	}
}

// Discard a card (removes from current hand and adds to discards)
void Player::discard(Card c) {

	if (listLegal().size() == 0 && (find(currCards.begin(), currCards.end(), c) != currCards.end())) {
		currCards.erase(remove(currCards.begin(), currCards.end(), c), currCards.end());
		discards.emplace_back(c);
		cout << "Player" << ID << " discards " << c << "." << endl;
	}
	else {
		throw Card(c);
	}
}

// Get current cards on hand
vector<Card> Player::getCurrCards() {
	return currCards;
}

// List of legal cards to play
vector<Card> Player::listLegal() {

	vector<Card> v;

	int handSize = currCards.size();
	int spadeSize = t->getSuiteCards("S").size();
	int heartSize = t->getSuiteCards("H").size();
	int diamondSize = t->getSuiteCards("D").size();
	int clubSize = t->getSuiteCards("C").size();

	for (int i = 0; i < handSize; ++i) {

		if ((currCards[i].getRank() == "7") && (currCards[i].getSuite() == "S")) {
			v.clear();			
			v.emplace_back(currCards[i]);
			return v;
		}
		else if (currCards[i].getRank() == "7") {
			v.emplace_back(currCards[i]);
		}

		else if (currCards[i].getSuite() == "S") {

			for (int j = 0; j < spadeSize; ++j) {
				if ((currCards[i].rankToInt() == t->getSuiteCards("S")[j].rankToInt() - 1) || (currCards[i].rankToInt() == t->getSuiteCards("S")[j].rankToInt() + 1)) {
					v.emplace_back(currCards[i]);
				}
			}
		}

		else if (currCards[i].getSuite() == "H") {

			for (int j = 0; j < heartSize; ++j) {
				if ((currCards[i].rankToInt() == t->getSuiteCards("H")[j].rankToInt() - 1) || (currCards[i].rankToInt() == t->getSuiteCards("H")[j].rankToInt() + 1)) {
					v.emplace_back(currCards[i]);
				}
			}
		}

		else if (currCards[i].getSuite() == "D") {

			for (int j = 0; j < diamondSize; ++j) {
				if ((currCards[i].rankToInt() == t->getSuiteCards("D")[j].rankToInt() - 1) || (currCards[i].rankToInt() == t->getSuiteCards("D")[j].rankToInt() + 1)) {
					v.emplace_back(currCards[i]);
				}
			}
		}

		else if (currCards[i].getSuite() == "C") {

			for (int j = 0; j < clubSize; ++j) {
				if ((currCards[i].rankToInt() == t->getSuiteCards("C")[j].rankToInt() - 1) || (currCards[i].rankToInt() == t->getSuiteCards("C")[j].rankToInt() + 1)) {
					v.emplace_back(currCards[i]);
				}
			}
		}

	}
	return v;
} 


// Get current discards
vector<Card> Player::listDiscard() {
	return discards;
}

// Get player ID
int Player::getID() {
	return ID;
}

// Get current score
int Player::getCurrScore() {
	int score = 0;
	int discardLength = discards.size();

	for (int i = 0; i < discardLength; ++i) {
		score += discards[i].rankToInt();
	}

	currScore = score;

	return currScore;

}

// Get total score
int Player::getTotalScore() {
	return totalScore;
}


// Add card to current hand
void Player::addCard(Card c) {
	currCards.push_back(c);
}

// Clear current hand and discards
void Player::clearCards() {
	currCards.clear();
	discards.clear();
}

// Checks if player has 7 of Spades
bool Player::has7S() {
	int handLength = currCards.size();
	for (int i = 0; i < handLength; ++i) {
		if ((currCards[i].getRank() == "7") && (currCards[i].getSuite() == "S")) {
			return true;
		}
	}
	return false;
}

// Calculates final score
int Player::calcFinalScore() {
	return currScore + totalScore;
}

// Reset current score
void Player::reset() {
	totalScore += currScore;	
	currScore = 0;
}

// Add card to current discards (for ragequit)
void Player::addDiscard(Card c) {
	discards.push_back(c);
}

// Set current cards for new computer player after ragequit
void Player::setCurrCards(vector<Card> cards) {

	int handSize = cards.size();

	for (int i = 0; i < handSize; ++i) {
		addCard(cards[i]);
	}

}

// Set discards for new computer player after ragequit
void Player::setDiscards(vector<Card> cards) {
	int discardSize = cards.size();

	for (int i = 0; i < discardSize; ++i) {
		addDiscard(cards[i]);
	}
}

// Set total score
void Player::setTotalScore(int i) {
	totalScore = i;
}
