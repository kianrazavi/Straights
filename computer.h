#include <memory>
#include "table.h"
#include "player.h"
using namespace std;

#ifndef COMPUTER_H
#define COMPUTER_H

class Computer : public Player {

	public:

		// Constructor
		Computer(int ID, shared_ptr<Table> t);

		// Get player type
		string getType() override; 

		// Decide what card to play
		string moveLogic() override;

		// Plays move
		void compMove(string s) override;


};

#endif
