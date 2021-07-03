#include "table.h"
#include "player.h"
#include <memory>
using namespace std;

#ifndef HUMAN_H
#define HUMAN_H

class Human : public Player {

	public:

		// Constructor
		Human(int ID, shared_ptr<Table> t);

		// Get player type
		string getType() override;

		string moveLogic() override;
		void compMove(string s) override;

};

#endif
