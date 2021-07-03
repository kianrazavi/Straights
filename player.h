#include <memory>
#include <vector>
#include "subject.h"
#include "table.h"
#include "card.h"
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player {

	protected:

		shared_ptr<Table> t;
		int ID;
		int totalScore = 0;
		int currScore = 0;
		vector<Card> currCards;
		vector<Card> discards;

	public:

		// Constructor
		Player(int ID, shared_ptr<Table> table); 

		// Gets player type (i.e. Human or Computer)
		virtual string getType() = 0;

		// Put down a card
		void playCard(Card c);

		// Discard a card
		void discard(Card c);

		// Decides whether to move or discard for computer player
		virtual string moveLogic() = 0;

		// Plays or discards card for computer player
		virtual void compMove(string s) = 0;

		// Get current cards
		vector<Card> getCurrCards();

		// List cards legal to play
		vector<Card> listLegal();

		// List current discards
		vector<Card> listDiscard();

		// Get player ID
		int getID();

		// Get current score
		int getCurrScore();

		// Get total score
		int getTotalScore();

		// Add card to current hand
		void addCard(Card c);

		// Clear current hand
		void clearCards();

		// Checks if player has 7 of Spades
		bool has7S();

		// Computes final score
		int calcFinalScore();

		// Reset current score
		void reset();

		// Sets current cards after ragequit
		void setCurrCards(vector<Card> cards);

		// Sets current discards after ragequit
		void setDiscards(vector<Card> cards);

		// Add card to discard list (for ragequit)
		void addDiscard(Card c);

		// Set total score
		void setTotalScore(int i);

};

#endif
