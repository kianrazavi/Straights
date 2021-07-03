#include <memory>
#include "table.h"
#include "player.h"
#include "computer.h"
using namespace std;

// Constructor
Computer::Computer(int ID, shared_ptr<Table> t)
	: Player(ID, t)
{}

// Returns player type (in this case Computer)
string Computer::getType() {
	return "Computer";
}

// Decide whether to play or discard
string Computer::moveLogic() {

	if (!listLegal().empty()) {
		return "move";
	}
	return "discard";
}

// Plays move
void Computer::compMove(string s) {

	if (s == "move") {
		playCard(listLegal()[0]);
	}

	else {
		discard(getCurrCards()[0]);
	}

}



